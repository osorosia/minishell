/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:25:08 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/28 19:25:41 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	_vdprintf(int fd, const char *format, va_list ap)
{
	long	print_size;
	long	i;

	print_size = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			print_size += print_spec(format[++i], ap, fd);
		else
		{
			ft_putchar_fd(format[i], fd);
			print_size++;
		}
		i++;
	}
	return ((int)print_size);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		print_size;

	if (format == NULL)
		return (0);
	va_start(ap, format);
	print_size = _vdprintf(1, format, ap);
	va_end(ap);
	return (print_size);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		print_size;

	if (format == NULL)
		return (0);
	va_start(ap, format);
	print_size = _vdprintf(fd, format, ap);
	va_end(ap);
	return (print_size);
}
