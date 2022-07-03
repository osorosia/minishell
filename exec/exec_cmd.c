/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:26:05 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 11:45:06 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	set_redir_in(t_redir *redir_in)
{
	int	fd;

	if (redir_in == NULL)
		return (true);
	if (redir_in->kind == RD_IN)
	{
		fd = open(redir_in->str, O_RDONLY);
		if (fd < 0)
		{
			ft_dprintf_x(
				2, "minishell: %s: %s\n", redir_in->str, strerror(errno));
			return (false);
		}
	}
	else if (redir_in->kind == RD_HEREDOC)
		fd = redir_in->fd;
	else
		error("error: set_redir_in()");
	x_dup2(fd, 0);
	close(fd);
	return (set_redir_in(redir_in->next));
}

bool	set_redir_out(t_redir *redir_out)
{
	int	fd;
	int	oflag;

	if (redir_out == NULL)
		return (true);
	if (redir_out->kind == RD_OUT)
		oflag = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redir_out->kind == RD_APPEND)
		oflag = O_WRONLY | O_CREAT | O_APPEND;
	else
		error("error: set_redir_out()");
	fd = open(redir_out->str, oflag, 0664);
	if (fd < 0)
	{
		ft_dprintf_x(
			2, "minishell: %s: %s\n", redir_out->str, strerror(errno));
		return (false);
	}
	x_dup2(fd, 1);
	close(fd);
	return (set_redir_out(redir_out->next));
}

void	exec_cmd(t_node *node)
{
	if (g_shell->interrupt)
		return ;
	if (!set_redir_in(node->cmd->redir_in)
		|| !set_redir_out(node->cmd->redir_out)
		|| node->cmd->word == NULL)
	{
		x_dup2(g_shell->fd_stdout, 1);
		x_dup2(g_shell->fd_stdin, 0);
		g_shell->sts = 1;
		return ;
	}
	if (node->cmd->is_builtin)
		exec_builtin(node);
	else
		exec_file(node);
	x_dup2(g_shell->fd_stdout, 1);
	x_dup2(g_shell->fd_stdin, 0);
}
