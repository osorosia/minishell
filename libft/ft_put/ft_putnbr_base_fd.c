/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:22:53 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/28 19:24:29 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(long num, char *base, int fd)
{
	const long	base_len = ft_strlen(base);

	if (num < 0)
	{
		ft_putchar_fd('-', 1);
		num *= -1;
	}
	if (num / base_len != 0)
		ft_putnbr_base_fd(num / base_len, base, fd);
	ft_putchar_fd(base[num % base_len], 1);
}
