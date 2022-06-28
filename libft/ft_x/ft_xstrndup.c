/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:02:30 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/30 16:51:56 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	i;

	str = ft_xcalloc(n + 1, sizeof(char));
	i = 0;
	while (i < n)
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}
