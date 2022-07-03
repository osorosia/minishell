/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:26:05 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 11:19:39 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_stmt(t_node *stmt_node)
{
	if (stmt_node == NULL)
		return ;
	if (stmt_node->kind == ND_OR && g_shell->sts == 0)
	{
		exec_stmt(stmt_node->rhs);
		return ;
	}
	if (stmt_node->kind == ND_AND && g_shell->sts != 0)
	{
		exec_stmt(stmt_node->rhs);
		return ;
	}
	exec_pipe(stmt_node->lhs);
	exec_stmt(stmt_node->rhs);
}
