/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:02:30 by rnishimo          #+#    #+#             */
/*   Updated: 2022/06/28 12:42:21 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xstrndup(const char *s1, size_t n)
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
