/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:26:18 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:49:12 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	_get_word_len_to_space(char *str)
{
	bool	single_quote;
	bool	double_quote;
	long	i;

	single_quote = false;
	double_quote = false;
	i = 0;
	while (str[i])
	{
		if (!double_quote && !single_quote && str[i] == ' ')
			break ;
		if (double_quote && str[i] == '"')
			double_quote = false;
		if (single_quote && str[i] == '\'')
			single_quote = false;
		if (!single_quote && !double_quote && str[i] == '\'')
			single_quote = true;
		if (!single_quote && !double_quote && str[i] == '"')
			double_quote = true;
		i++;
	}
	return (i);
}

t_word	*word_last(t_word *word)
{
	while (word->next)
		word = word->next;
	return (word);
}

void	word_add_back(t_word *word, char *str)
{
	t_word	*new;
	t_word	*last;

	if (str == NULL)
		return ;
	new = ft_xcalloc(1, sizeof(t_word));
	new->str = str;
	last = word_last(word);
	last->next = new;
}

t_word	*_split_space_in_word(t_word *word)
{
	t_word	new_word;
	char	*str;
	long	i;
	long	len;
	t_word	*last;

	if (word == NULL)
		return (NULL);
	new_word.next = NULL;
	i = 0;
	while (word->str[i])
	{
		while (word->str[i] == ' ')
			i++;
		if (word->str[i] == '\0')
			break ;
		len = _get_word_len_to_space(&(word->str[i]));
		str = ft_xstrndup(&(word->str[i]), len);
		word_add_back(&new_word, str);
		i += len;
	}
	last = word_last(&new_word);
	last->next = _split_space_in_word(word->next);
	free(word->str);
	free(word);
	return (new_word.next);
}

void	split_space(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == ND_STMT)
		return ;
	if (node->kind == ND_CMD)
		node->cmd->word = _split_space_in_word(node->cmd->word);
	else
	{
		split_space(node->lhs);
		split_space(node->rhs);
	}
}

void	split_space_for_debug(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == ND_CMD)
		node->cmd->word = _split_space_in_word(node->cmd->word);
	else
	{
		split_space_for_debug(node->lhs);
		split_space_for_debug(node->rhs);
	}
}
