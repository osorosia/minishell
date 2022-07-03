/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bracket.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:26:05 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 11:21:37 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_bracket(t_node *bracket_node)
{
	int	pid;
	int	sts;

	if (bracket_node->kind == ND_BRACKET)
	{
		pid = x_fork();
		if (pid == 0)
		{
			exec_stmt(bracket_node->lhs);
			exit(g_shell->sts);
		}
		sts = 0;
		waitpid(pid, &sts, 0);
		g_shell->sts = WEXITSTATUS(sts);
	}
	else
		exec_cmd(bracket_node);
}
