/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:51:31 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 14:02:45 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_expand_asterisk_in_word(t_word *word)
{
	if (word == NULL)
		return ;
	_expand_asterisk_in_word(word->next);
}

void	_expand_asterisk_in_redir(t_redir *redir)
{
	if (redir == NULL)
		return ;
	_expand_asterisk_in_redir(redir->next);
}

void	expand_asterisk(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == ND_STMT)
		return ;
	if (node->kind == ND_CMD)
	{
		_expand_asterisk_in_word(node->cmd->word);
		_expand_asterisk_in_redir(node->cmd->redir_in);
		_expand_asterisk_in_redir(node->cmd->redir_out);
	}
	else
	{
		expand_asterisk(node->lhs);
		expand_asterisk(node->rhs);
	}
}
