/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:27:24 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/28 19:27:25 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	spec_d(va_list ap, int fd)
{
	int	num;

	num = va_arg(ap, int);
	ft_putnbr_base_fd(num, "0123456789", fd);
	return (ft_numlen(num, 10));
}
