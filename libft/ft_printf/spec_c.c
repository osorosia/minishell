/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:27:27 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/28 19:27:27 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	spec_c(va_list ap, int fd)
{
	char	c;

	c = (char)va_arg(ap, int);
	ft_putchar_fd(c, fd);
	return (1);
}
