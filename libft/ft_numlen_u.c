/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:49:06 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/29 22:30:39 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen_u(unsigned long long num)
{
	size_t		len;
	const int	base = 10;

	if (base == 0)
		return (0);
	if (num == 0)
		return (1);
	len = 0;
	while (num != 0)
	{
		num /= base;
		len++;
	}
	return (len);
}
