/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:49:06 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/29 17:06:44 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen(long long num)
{
	size_t		len;
	const int	base = 10;

	if (base == 0)
		return (0);
	if (num == 0)
		return (1);
	if (num == LONG_MIN)
		num++;
	len = 0;
	if (num < 0)
		len++;
	while (num != 0)
	{
		num /= base;
		len++;
	}
	return (len);
}
