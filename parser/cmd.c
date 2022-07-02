/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:07:28 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:25:59 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
