/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:29:01 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 15:17:56 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_var_name_char_1st(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_var_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
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
