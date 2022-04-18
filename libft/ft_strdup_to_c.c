/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:47:27 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/09 23:24:13 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_to_c(const char *s1, char c)
{
	char	*str;
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen_to_c(s1, c);
	str = (char *)malloc(sizeof(char) * str_len + 2);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}
