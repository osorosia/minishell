/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:07:28 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:39:58 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*_new_node_cmd(void)
{
	t_node	*node;

	node = ft_xcalloc(1, sizeof(t_node));
	node->cmd = ft_xcalloc(1, sizeof(t_cmd));
	node->kind = ND_CMD;
	return (node);
}

void	_add_word(t_cmd *cmd, char *str, long len)
{
	t_word	*word;
	t_word	*now;

	word = ft_xcalloc(1, sizeof(t_word));
	word->str = ft_xstrndup(str, len);
	if (!cmd->word)
		cmd->word = word;
	else
	{
		now = cmd->word;
		while (now->next)
			now = now->next;
		now->next = word;
	}
}

void	_add_redir_in(t_cmd *cmd, t_redir_kind kind, char *str, long len)
{
	t_redir	*redir;
	t_redir	*now;

	redir = ft_xcalloc(1, sizeof(t_redir));
	redir->fd = -1;
	redir->str = ft_xstrndup(str, len);
	redir->kind = kind;
	if (!cmd->redir_in)
		cmd->redir_in = redir;
	else
	{
		now = cmd->redir_in;
		while (now->next)
			now = now->next;
		now->next = redir;
	}
}

void	_add_redir_out(t_cmd *cmd, t_redir_kind kind, char *str, long len)
{
	t_redir	*redir;
	t_redir	*now;

	redir = ft_xcalloc(1, sizeof(t_redir));
	redir->fd = -1;
	redir->str = ft_xstrndup(str, len);
	redir->kind = kind;
	if (!cmd->redir_out)
		cmd->redir_out = redir;
	else
	{
		now = cmd->redir_out;
		while (now->next)
			now = now->next;
		now->next = redir;
	}
}
