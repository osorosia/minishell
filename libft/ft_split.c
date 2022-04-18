/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 23:46:44 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/13 00:42:40 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	_get_strs_len(char const *s, char c)
{
	size_t	strs_len;

	strs_len = 0;
	while (*s != '\0')
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			strs_len++;
		s++;
	}
	return (strs_len);
}

static size_t	_get_str_len(char const *s, char c)
{
	size_t	str_len;

	str_len = 0;
	while (*s != c && *s != '\0')
	{
		str_len++;
		s++;
	}
	return (str_len);
}

static char	*_get_str(char const *s, size_t str_len)
{
	return (ft_substr(s, 0, str_len));
}

static bool	_get_strs_recursive(char **strs, char const *s, char c)
{
	size_t	str_len;

	while (*s && *s == c)
		s++;
	if (*s == '\0')
	{
		*strs = NULL;
		return (true);
	}
	str_len = _get_str_len(s, c);
	*strs = _get_str(s, str_len);
	if (*strs == NULL)
		return (false);
	if (!_get_strs_recursive(strs + 1, s + str_len, c))
	{
		free(*strs);
		return (false);
	}
	return (true);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	strs_len;

	if (s == NULL)
		return (NULL);
	strs_len = _get_strs_len(s, c);
	strs = (char **)malloc(sizeof(char *) * (strs_len + 1));
	if (strs == NULL)
		return (NULL);
	if (!_get_strs_recursive(strs, s, c))
	{
		free(strs);
		return (NULL);
	}
	return (strs);
}
