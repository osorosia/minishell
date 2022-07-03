/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_set_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:21:53 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 11:03:06 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_heredoc(t_redir *redir)
{
	int		fd[2];
	char	*line;

	if (redir == NULL)
		return ;
	if (redir->kind == RD_HEREDOC)
	{
		x_pipe(fd);
		redir->fd = fd[0];
		while (1)
		{
			ft_putstr_fd("> ", 2);
			line = get_next_line(0);
			if (line == NULL)
				break ;
			if (g_shell->is_test)
				write(1, line, ft_strlen(line));
			if (ft_strlen(line) > 1
				&& ft_strncmp(line, redir->str, ft_strlen(line) - 1) == 0)
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
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
