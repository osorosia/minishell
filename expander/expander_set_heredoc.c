/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_set_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:21:53 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 13:44:15 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_heredoc_eof(char *line, char *eof)
{
	long	line_len;

	line_len = ft_strlen(line) - 1;
	return (line_len > 0 && ft_strncmp(line, eof, line_len) == 0);
}

void	write_heredoc_to_fd(t_redir *redir, int fd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (g_shell->is_test)
			write(1, line, ft_strlen(line));
		if (is_heredoc_eof(line, redir->str))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

void	set_heredoc(t_redir *redir)
{
	int		fd[2];

	if (redir == NULL)
		return ;
	if (g_shell->interrupt)
		return ;
	if (redir->kind == RD_HEREDOC)
	{
		x_pipe(fd);
		redir->fd = fd[0];
		write_heredoc_to_fd(redir, fd[1]);
		x_dup2(g_shell->fd_stdin, 0);
		ft_xclose(fd[1]);
	}
	set_heredoc(redir->next);
}

void	expander_set_heredoc(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == ND_CMD)
	{
		delete_quote_in_heredoc(node->cmd->redir_in);
		set_heredoc(node->cmd->redir_in);
	}
	else
	{
		expander_set_heredoc(node->rhs);
		expander_set_heredoc(node->lhs);
	}
}
