/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unumlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:23:54 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/28 19:24:20 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_unumlen(size_t num, long base)
{
	long	len;

	len = 0;
	while (true)
	{
		len++;
		num /= base;
		if (num == 0)
			break ;
	}
	return (len);
}
