/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:51:31 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 16:25:04 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_match_asterisk(char *pattern, char *str, long p_i, long str_i)
{
	if (p_i == 0 && str_i == 0 && pattern[p_i] != '.' && is_hidden_file(str))
		return (false);
	if (str[str_i] == '\0')
	{
		while (pattern[p_i] != '\0')
		{
			if (pattern[p_i] != '*')
				return (false);
			p_i++;
		}
		return (true);
	}
	if (pattern[p_i] == '*')
		return (is_match_asterisk(pattern, str, p_i, str_i + 1)
			|| is_match_asterisk(pattern, str, p_i + 1, str_i));
	else if (pattern[p_i] == str[str_i])
		return (is_match_asterisk(pattern, str, p_i + 1, str_i + 1));
	return (false);
}

char	**matched_arr_asterisk(char *str)
{
	char			**arr;
	DIR				*dir;
	struct dirent	*ent;

	arr = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	while (true)
	{
		ent = readdir(dir);
		if (ent == NULL)
			break ;
		if (is_match_asterisk(str, ent->d_name, 0, 0))
			arr = arr_add_back(arr, ent->d_name);
	}
	closedir(dir);
	if (arr != NULL)
		sort_arr(arr);
	return (arr);
}

void	word_add_back_asterisk(t_word *word, char *str)
{
	t_word	*new;
	t_word	*last;

	if (str == NULL)
		return ;
	new = ft_xcalloc(1, sizeof(t_word));
	new->str = str;
	new->dont_expand = true;
	last = word_last(word);
	last->next = new;
}

t_word	*create_word_expanded_asterisk(char *str)
{
	char	**arr;
	long	i;
	t_word	new_word;

	arr = matched_arr_asterisk(str);
	if (arr == NULL)
		return (NULL);
	new_word.next = NULL;
	i = 0;
	while (arr[i])
		word_add_back_asterisk(&new_word, arr[i++]);
	free(arr);
	return (new_word.next);
}
