/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:07:28 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 10:25:45 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_redir_in(t_token **tok, t_node *node)
{
	if (equal(*tok, TK_OP, "<<"))
	{
		*tok = skip(*tok, TK_OP, "<<");
		_add_redir_in(node->cmd, RD_HEREDOC, (*tok)->str, (*tok)->len);
	}
	else if (equal(*tok, TK_OP, "<"))
	{
		*tok = skip(*tok, TK_OP, "<");
		_add_redir_in(node->cmd, RD_IN, (*tok)->str, (*tok)->len);
	}
}

void	cmd_redir_out(t_token **tok, t_node *node)
{
	if (equal(*tok, TK_OP, ">>"))
	{
		*tok = skip(*tok, TK_OP, ">>");
		_add_redir_out(node->cmd, RD_APPEND, (*tok)->str, (*tok)->len);
	}
	else if (equal(*tok, TK_OP, ">"))
	{
		*tok = skip(*tok, TK_OP, ">");
		_add_redir_out(node->cmd, RD_OUT, (*tok)->str, (*tok)->len);
	}
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
		else if (equal(*tok, TK_OP, "<<") || equal(*tok, TK_OP, "<"))
			cmd_redir_in(tok, node);
		else if (equal(*tok, TK_OP, ">>") || equal(*tok, TK_OP, ">"))
			cmd_redir_out(tok, node);
		else
		{
			if (node->cmd->word == NULL && node->cmd->redir_in == NULL
				&& node->cmd->redir_out == NULL)
				syntax_error((*tok)->str, (*tok)->len);
			return (node);
		}
		*tok = skip(*tok, TK_WORD, NULL);
	}
}
