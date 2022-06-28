/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:20:22 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/28 19:22:43 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_numlen(long num, long base)
{
	long	len;

	len = 0;
	if (num < 0)
	{
		num *= -1;
		len++;
	}
	while (true)
	{
		len++;
		num /= base;
		if (num == 0)
			break ;
	}
	return (len);
}
