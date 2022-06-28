/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrdup_to_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 20:47:27 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/30 16:57:16 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xstrdup_to_c(const char *s1, char c)
{
	char	*str;
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen_to_c(s1, c);
	str = ft_xmalloc(sizeof(char) * str_len + 2);
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
