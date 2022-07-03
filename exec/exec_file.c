/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 11:36:55 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 13:40:15 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fail_exec(t_node *node)
{
	g_shell->sts = 126;
	if (errno == ENOENT)
		g_shell->sts = 127;
	ft_dprintf_x(
		2, "minishell: %s: %s\n", node->cmd->pathname, strerror(errno));
	return (g_shell->sts);
}

bool	check_cmd(t_cmd *cmd)
{
	if (cmd->pathname == NULL)
	{
		ft_dprintf_x(2, "minishell: %s: command not found\n",
			cmd->word->str);
		g_shell->sts = 127;
		return (false);
	}
	if (is_directory(cmd->pathname))
	{
		ft_dprintf_x(
			2, "minishell: %s: is a directory\n", cmd->pathname);
		g_shell->sts = 126;
		return (false);
	}
	return (true);
}

void	set_exit_status(void)
{
	if (WIFSIGNALED(g_shell->sts))
	{
		g_shell->sts = 128 + WTERMSIG(g_shell->sts);
		if (g_shell->sts == 128 + SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
	}
	else
		g_shell->sts = WEXITSTATUS(g_shell->sts);
}

void	exec_file(t_node *node)
{
	int		pid;
	char	**cmd_argv;
	char	**cmd_envp;

	pid = x_fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (!check_cmd(node->cmd))
			exit(g_shell->sts);
		cmd_argv = create_argv(node->cmd->word);
		cmd_envp = create_envp();
		execve(node->cmd->pathname, cmd_argv, cmd_envp);
		free(cmd_argv);
		free_envp(cmd_envp);
		exit(fail_exec(node));
	}
	waitpid(pid, &(g_shell->sts), 0);
	set_exit_status();
}
