/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:49:06 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/29 19:54:39 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen_base(long long num, int base)
{
	size_t	len;

	if (base == 0)
		return (0);
	if (num == 0)
		return (1);
	if (num == LLONG_MIN)
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
