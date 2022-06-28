/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_xX.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:27:15 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/28 19:27:17 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	spec_x(va_list ap, int fd)
{
	unsigned int	num;

	num = va_arg(ap, unsigned int);
	ft_putunbr_base_fd(num, "0123456789abcdef", fd);
	return (ft_unumlen(num, 16));
}

long	spec_X(va_list ap, int fd)
{
	unsigned int	num;

	num = va_arg(ap, unsigned int);
	ft_putunbr_base_fd(num, "0123456789ABCDEF", fd);
	return (ft_unumlen(num, 16));
}
