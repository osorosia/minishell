/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:25:08 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 20:50:20 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	_vdprintf_x(int fd, const char *format, va_list ap)
{
	long	i;
	long	len;
	char	*str;
	char	*spec_str;

	str = ft_xstrdup("");
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			spec_str = xspec(ap, format[++i]);
			if (spec_str && i++)
				str = ft_xstrjoin_with_free(str, true, spec_str, true);
		}
		len = ft_strlen_to_c(&(format[i]), '%');
		if (len > 0)
			str = ft_xstrjoin_with_free(
					str, true, ft_xstrndup(&(format[i]), len), true);
		i += len;
	}
	ft_putstr_fd(str, fd);
	return ((int)ft_strlen(str));
}

int	ft_printf_x(const char *format, ...)
{
	va_list	ap;
	int		print_size;

	if (format == NULL)
		return (0);
	va_start(ap, format);
	print_size = _vdprintf_x(1, format, ap);
	va_end(ap);
	return (print_size);
}

int	ft_dprintf_x(int fd, const char *format, ...)
{
	va_list	ap;
	int		print_size;

	if (format == NULL)
		return (0);
	va_start(ap, format);
	print_size = _vdprintf_x(fd, format, ap);
	va_end(ap);
	return (print_size);
}
