/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:07:28 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:26:16 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
