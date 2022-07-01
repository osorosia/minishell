/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:07:28 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:52:57 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*_new_node_stmt(t_node_kind kind, t_node *pipe_cmd_node)
{
	t_node	*node;

	node = ft_xcalloc(1, sizeof(t_node));
	node->kind = kind;
	node->lhs = pipe_cmd_node;
	return (node);
}

void	_add_node_stmt(t_node *node, t_node_kind kind, t_node *bracket_node)
{
	while (node->rhs)
		node = node->rhs;
	node->rhs = _new_node_stmt(kind, bracket_node);
}

void	*_new_node_bracket(t_node *stmt_node)
{
	t_node	*node;

	node = ft_xcalloc(1, sizeof(t_node));
	node->kind = ND_BRACKET;
	node->lhs = stmt_node;
	return (node);
}

t_node	*_new_node_pipe(t_node *cmd_node)
{
	t_node	*node;

	node = ft_xcalloc(1, sizeof(t_node));
	node->kind = ND_PIPE;
	node->rhs = cmd_node;
	return (node);
}

t_node	*_add_node_pipe(t_node *node, t_node *cmd_node)
{
	t_node	*new;

	new = _new_node_pipe(cmd_node);
	new->lhs = node;
	return (new);
}

t_node	*_new_node_cmd(void)
{
	t_node	*node;

	node = ft_xcalloc(1, sizeof(t_node));
	node->cmd = ft_xcalloc(1, sizeof(t_cmd));
	node->kind = ND_CMD;
	return (node);
}

void	_add_word(t_cmd *cmd, char *str, long len)
{
	t_word	*word;
	t_word	*now;

	word = ft_xcalloc(1, sizeof(t_word));
	word->str = ft_xstrndup(str, len);
	if (!cmd->word)
		cmd->word = word;
	else
	{
		now = cmd->word;
		while (now->next)
			now = now->next;
		now->next = word;
	}
}

void	_add_redir_in(t_cmd *cmd, t_redir_kind kind, char *str, long len)
{
	t_redir	*redir;
	t_redir	*now;

	redir = ft_xcalloc(1, sizeof(t_redir));
	redir->fd = -1;
	redir->str = ft_xstrndup(str, len);
	redir->kind = kind;
	if (!cmd->redir_in)
		cmd->redir_in = redir;
	else
	{
		now = cmd->redir_in;
		while (now->next)
			now = now->next;
		now->next = redir;
	}
}

void	_add_redir_out(t_cmd *cmd, t_redir_kind kind, char *str, long len)
{
	t_redir	*redir;
	t_redir	*now;

	redir = ft_xcalloc(1, sizeof(t_redir));
	redir->fd = -1;
	redir->str = ft_xstrndup(str, len);
	redir->kind = kind;
	if (!cmd->redir_out)
		cmd->redir_out = redir;
	else
	{
		now = cmd->redir_out;
		while (now->next)
			now = now->next;
		now->next = redir;
	}
}

t_node	*parser(t_token *tok);
t_node	*stmt(t_token **tok);
t_node	*bracket(t_token **tok);
t_node	*pipe_cmd(t_token **tok);
t_node	*cmd(t_token **tok);

t_node	*word(t_token **tok);
t_node	*redir_in(t_token **tok);
t_node	*redir_out(t_token **tok);

// parser = stmt EOF
t_node	*parser(t_token *tok)
{
	t_node	*node;

	node = stmt(&tok);
	tok = skip(tok, TK_EOF, NULL);
	return (node);
}

// stmt = pipe_cmd ((";" | "||" | "&&") pipe_cmd)* ";"?
t_node	*stmt(t_token **tok)
{
	t_node	*node;

	node = _new_node_stmt(ND_STMT, pipe_cmd(tok));
	while (true)
	{
		if (equal(*tok, TK_OP, ";") && !equal((*tok)->next, TK_EOF, NULL)
			&& !equal((*tok)->next, TK_OP, ")"))
		{
			*tok = skip(*tok, TK_OP, ";");
			_add_node_stmt(node, ND_STMT, pipe_cmd(tok));
		}
		else if (equal(*tok, TK_OP, "||"))
		{
			*tok = skip(*tok, TK_OP, "||");
			_add_node_stmt(node, ND_OR, pipe_cmd(tok));
		}
		else if (equal(*tok, TK_OP, "&&"))
		{
			*tok = skip(*tok, TK_OP, "&&");
			_add_node_stmt(node, ND_AND, pipe_cmd(tok));
		}
		else
			break ;
	}
	if (equal(*tok, TK_OP, ";"))
		*tok = skip(*tok, TK_OP, ";");
	return (node);
}

// pipe_cmd = bracket ("|" bracket)*
t_node	*pipe_cmd(t_token **tok)
{
	t_node	*node;

	node = _new_node_pipe(bracket(tok));
	while (equal(*tok, TK_OP, "|"))
	{
		*tok = skip(*tok, TK_OP, "|");
		node = _add_node_pipe(node, bracket(tok));
	}
	return (node);
}

// bracket = "(" stmt ")"
//         | cmd
t_node	*bracket(t_token **tok)
{
	t_node	*node;

	if (equal(*tok, TK_OP, "("))
	{
		*tok = skip(*tok, TK_OP, "(");
		node = _new_node_bracket(stmt(tok));
		*tok = skip(*tok, TK_OP, ")");
	}
	else
		node = cmd(tok);
	return (node);
}

// cmd = (word | redir_in | redir_out)*
t_node	*cmd(t_token **tok)
{
	t_node	*node;

	node = _new_node_cmd();
	while (true)
	{
		if (equal(*tok, TK_WORD, NULL))
			_add_word(node->cmd, (*tok)->str, (*tok)->len);
		else if (equal(*tok, TK_OP, "<<"))
		{
			*tok = skip(*tok, TK_OP, "<<");
			_add_redir_in(node->cmd, RD_HEREDOC, (*tok)->str, (*tok)->len);
		}
		else if (equal(*tok, TK_OP, "<"))
		{
			*tok = skip(*tok, TK_OP, "<");
			_add_redir_in(node->cmd, RD_IN, (*tok)->str, (*tok)->len);
		}
		else if (equal(*tok, TK_OP, ">>"))
		{
			*tok = skip(*tok, TK_OP, ">>");
			_add_redir_out(node->cmd, RD_APPEND, (*tok)->str, (*tok)->len);
		}
		else if (equal(*tok, TK_OP, ">"))
		{
			*tok = skip(*tok, TK_OP, ">");
			_add_redir_out(node->cmd, RD_OUT, (*tok)->str, (*tok)->len);
		}
		else
		{
			if (node->cmd->word == NULL && node->cmd->redir_in == NULL
				&& node->cmd->redir_out == NULL)
			{
				ft_putstr_fd(
					"minishell: syntax error near unexpected token `", 2);
				ft_putnstr_fd((*tok)->str, (*tok)->len, 2);
				ft_putstr_fd("'\n", 2);
				exit(1);
			}
			return (node);
		}
		*tok = skip(*tok, TK_WORD, NULL);
	}
}
