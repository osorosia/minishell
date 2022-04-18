/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:35:01 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/09 22:34:31 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_to_c(const char *str, const char c)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}
