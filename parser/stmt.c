/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stmt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:07:28 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:31:16 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*stmt_in_asta(t_token **tok, t_node *node)
{
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
	return (node);
}

// stmt = pipe_cmd ((";" | "||" | "&&") pipe_cmd)* ";"?
t_node	*stmt(t_token **tok)
{
	t_node	*node;

	node = _new_node_stmt(ND_STMT, pipe_cmd(tok));
	stmt_in_asta(tok, node);
	if (equal(*tok, TK_OP, ";"))
		*tok = skip(*tok, TK_OP, ";");
	return (node);
}
