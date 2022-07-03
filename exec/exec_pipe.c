/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:26:05 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 11:21:04 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_no_pipe(t_node *pipe_node)
{
	exec_bracket(pipe_node->rhs);
}

void	exec_multi_pipes(t_node *pipe_node)
{
	int	fd[2];
	int	pid;
	int	sts;

	if (pipe_node == NULL)
		return ;
	x_pipe(fd);
	pid = x_fork();
	if (pid == 0)
	{
		if (pipe_node->lhs)
			x_dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		exec_bracket(pipe_node->rhs);
		exit(g_shell->sts);
	}
	else
	{
		x_dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		exec_multi_pipes(pipe_node->lhs);
	}
	sts = 0;
	waitpid(pid, &sts, 0);
	g_shell->sts = WEXITSTATUS(sts);
}

void	exec_pipe(t_node *pipe_node)
{
	int	pid;
	int	sts;

	expander(pipe_node);
	if (pipe_node->lhs == NULL)
		exec_no_pipe(pipe_node);
	else
	{
		pid = x_fork();
		if (pid == 0)
		{
			exec_multi_pipes(pipe_node);
			exit(g_shell->sts);
		}
		sts = 0;
		waitpid(pid, &sts, 0);
		g_shell->sts = WEXITSTATUS(sts);
	}
}
