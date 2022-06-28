/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:25:52 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/28 19:26:50 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	print_spec(char c, va_list ap, int fd)
{
	if (c == 'c')
		return (spec_c(ap, fd));
	if (c == 's')
		return (spec_s(ap, fd));
	if (c == 'p')
		return (spec_p(ap, fd));
	if (c == 'd' || c == 'i')
		return (spec_d(ap, fd));
	if (c == 'u')
		return (spec_u(ap, fd));
	if (c == 'x')
		return (spec_x(ap, fd));
	if (c == 'X')
		return (spec_X(ap, fd));
	ft_putchar_fd(c, 1);
	return (1);
}
