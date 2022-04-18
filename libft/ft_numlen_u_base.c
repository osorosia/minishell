/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen_u_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:49:06 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/29 22:31:00 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen_u_base(unsigned long long num, unsigned int base)
{
	size_t	len;

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
