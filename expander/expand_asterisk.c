/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:51:31 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 15:51:39 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
t_word	*_expand_asterisk_in_word(t_word *word)
{
	t_word	*new_word;
	t_word	*new_word_last;

	if (word == NULL)
		return (NULL);
	if (exist_asterisk(word->str))
	{
		new_word = create_word_expanded_asterisk(word->str);
		if (new_word)
		{
			new_word_last = word_last(new_word);
			new_word_last->next = _expand_asterisk_in_word(word->next);
			free(word->str);
			free(word);
			word = new_word;
		}
		else
			word->next = _expand_asterisk_in_word(word->next);
	}
	else
		word->next = _expand_asterisk_in_word(word->next);
	return (word);
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
		node->cmd->word = _expand_asterisk_in_word(node->cmd->word);
		_expand_asterisk_in_redir(node->cmd->redir_in);
		_expand_asterisk_in_redir(node->cmd->redir_out);
	}
	else
	{
		expand_asterisk(node->lhs);
		expand_asterisk(node->rhs);
	}
}
