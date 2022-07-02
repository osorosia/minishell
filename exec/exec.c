/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:26:05 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 19:55:04 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd(t_node *node);
void	exec_bracket(t_node *pipe_node);
void	exec_no_pipe(t_node *pipe_node);
void	exec_pipe(t_node *pipe_node);
void	exec_stmt(t_node *stmt_node);

char	**create_argv(t_word *word)
{
	char	**argv;
	long	len;
	t_word	*now;
	long	i;

	len = 0;
	now = word;
	while (now)
	{
		len++;
		now = now->next;
	}
	argv = ft_xcalloc(len + 1, sizeof(char *));
	i = 0;
	while (word)
	{
		argv[i] = word->str;
		i++;
		word = word->next;
	}
	return (argv);
}

void	exec_builtin(t_node *node)
{
	t_cmd		*cmd;
	long		i;
	static	int	(*builtin_fn[])(t_word *) = {
		exec_echo, exec_cd, exec_pwd, exec_export,
		exec_unset, exec_env, exec_exit, NULL};
	static char	*kw[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	cmd = node->cmd;
	i = 0;
	while (kw[i])
	{
		if (strcmp(kw[i], cmd->word->str) == 0)
		{
			g_shell->sts = builtin_fn[i](cmd->word);
			break ;
		}
		i++;
	}
	if (kw[i] == NULL)
		error("no match builtin");
}

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
			ft_dprintf(2, "minishell: %s: %s\n", redir_in->str, strerror(errno));
			return (false);
		}
		dup2(fd, 0);
		close(fd);
	}
	else if (redir_in->kind == RD_HEREDOC)
	{
		if (redir_in->fd >= 0)
			dup2(redir_in->fd, 0);
		else
			error("error: redir_in: heredoc");
	}
	else
	{
		error("error: set_redir_in()");
	}
	return (set_redir_in(redir_in->next));
}

bool	set_redir_out(t_redir *redir_out)
{
	int	fd;

	if (redir_out == NULL)
		return (true);
	if (redir_out->kind == RD_OUT)
	{
		fd = open(redir_out->str, (O_WRONLY | O_CREAT | O_TRUNC), 0664);
		if (fd < 0)
		{
			ft_dprintf(2, "minishell: %s: %s\n",
				redir_out->str, strerror(errno));
			return (false);
		}
		dup2(fd, 1);
		close(fd);
	}
	else if (redir_out->kind == RD_APPEND)
	{
		fd = open(redir_out->str, (O_WRONLY | O_CREAT | O_APPEND), 0664);
		if (fd < 0)
		{
			ft_dprintf(2, "minishell: %s: %s\n",
				redir_out->str, strerror(errno));
			return (false);
		}
		dup2(fd, 1);
		close(fd);
	}
	else
		error("error: set_redir_out()");
	return (set_redir_out(redir_out->next));
}

bool	is_directory(char *pathname)
{
	struct stat	st;

	if (stat(pathname, &st) != 0)
		return (false);
	return (S_ISDIR(st.st_mode));
}

void	exec_cmd(t_node *node)
{
	int		pid;
	int		sts;
	char	**cmd_argv;
	char	**cmd_envp;

	if (g_shell->interrupt)
		return ;
	if (!set_redir_in(node->cmd->redir_in) || !set_redir_out(node->cmd->redir_out))
	{
		g_shell->sts = 1;
		dup2(g_shell->fd_stdout, 1);
		dup2(g_shell->fd_stdin, 0);
		return ;
	}
	if (node->cmd->word == NULL)
	{
		dup2(g_shell->fd_stdout, 1);
		dup2(g_shell->fd_stdin, 0);
		g_shell->sts = 0;
		return ;
	}
	if (node->cmd->is_builtin)
		exec_builtin(node);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (node->cmd->pathname == NULL)
			{
				ft_dprintf(2, "minishell: %s: command not found\n",
					node->cmd->word->str);
				exit(127);
			}
			if (is_directory(node->cmd->pathname))
			{
				ft_dprintf(2, "minishell: %s: is a directory\n", node->cmd->pathname);
				exit(126);
			}
			cmd_argv = create_argv(node->cmd->word);
			cmd_envp = create_envp();
			execve(node->cmd->pathname, cmd_argv, cmd_envp);
			sts = 126;
			if (errno == ENOENT)
				sts = 127;
			ft_dprintf(2, "minishell: %s: %s\n", node->cmd->pathname, strerror(errno));
			free(cmd_argv);
			free_envp(cmd_envp);
			exit(sts);
		}
		waitpid(pid, &sts, 0);
		g_shell->sts = WEXITSTATUS(sts);
	}
	dup2(g_shell->fd_stdout, 1);
	dup2(g_shell->fd_stdin, 0);
}

void	exec_bracket(t_node *bracket_node)
{
	int	pid;
	int	sts;

	if (bracket_node->kind == ND_BRACKET)
	{
		pid = fork();
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

void	exec_no_pipe(t_node *pipe_node)
{
	exec_bracket(pipe_node->rhs);
}

void	exec_pipes(t_node *pipe_node)
{
	int	fd[2];
	int	pid;
	int	sts;

	if (pipe_node == NULL)
		return ;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (pipe_node->lhs)
			dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		exec_bracket(pipe_node->rhs);
		exit(g_shell->sts);
	}
	else
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		exec_pipes(pipe_node->lhs);
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
		pid = fork();
		if (pid == 0)
		{
			exec_pipes(pipe_node);
			exit(g_shell->sts);
		}
		sts = 0;
		waitpid(pid, &sts, 0);
		g_shell->sts = WEXITSTATUS(sts);
	}
}

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

void	exec(t_node *node)
{
	exec_stmt(node);
}
