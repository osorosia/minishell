/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:51:31 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 16:25:28 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	exist_asterisk(char *str)
{
	bool	single_quote;
	bool	double_quote;
	long	i;

	single_quote = false;
	double_quote = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !double_quote)
			single_quote ^= 1;
		else if (str[i] == '"' && !single_quote)
			double_quote ^= 1;
		else if (str[i] == '*' && !single_quote && !double_quote)
			return (true);
		i++;
	}
	return (false);
}

void	sort_arr(char **arr)
{
	long	i;
	long	j;
	char	*tmp;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[++j])
		{
			if (ft_strcmp(arr[i], arr[j]) < 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

bool	is_hidden_file(char *str)
{
	return (str[0] == '.');
}

char	**arr_add_back(char **arr, char *str)
{
	char	**new;
	long	len;
	long	i;

	len = 0;
	while (arr && arr[len])
		len++;
	new = ft_xcalloc(len + 2, sizeof(char *));
	i = 0;
	while (arr && arr[i])
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = ft_xstrdup(str);
	free(arr);
	return (new);
}
