/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:07:28 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:26:05 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
