/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:36:55 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 11:37:17 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_file(t_node *node)
{
	int		pid;
	char	**cmd_argv;
	char	**cmd_envp;

	pid = x_fork();
	if (pid == 0)
	{
		if (node->cmd->pathname == NULL)
		{
			ft_dprintf_x(2, "minishell: %s: command not found\n",
				node->cmd->word->str);
			exit(127);
		}
		if (is_directory(node->cmd->pathname))
		{
			ft_dprintf_x(
				2, "minishell: %s: is a directory\n", node->cmd->pathname);
			exit(126);
		}
		cmd_argv = create_argv(node->cmd->word);
		cmd_envp = create_envp();
		execve(node->cmd->pathname, cmd_argv, cmd_envp);
		g_shell->sts = 126;
		if (errno == ENOENT)
			g_shell->sts = 127;
		ft_dprintf_x(
			2, "minishell: %s: %s\n", node->cmd->pathname, strerror(errno));
		free(cmd_argv);
		free_envp(cmd_envp);
		exit(g_shell->sts);
	}
	waitpid(pid, &(g_shell->sts), 0);
	g_shell->sts = WEXITSTATUS(g_shell->sts);
}
