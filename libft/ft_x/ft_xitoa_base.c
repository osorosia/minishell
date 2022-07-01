/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:23:13 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 08:57:50 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_abs(int n)
{
	if (n < 0)
		return (-1 * n);
	return (n);
}

static void	_get_str_recursive(char *str, size_t str_i, int n, char *base)
{
	const size_t	base_len = ft_strlen(base);

	if (n < 0)
		str[0] = '-';
	str[str_i] = base[_abs(n % base_len)];
	if (n / base_len != 0)
		_get_str_recursive(str, str_i - 1, _abs(n / base_len), base);
}

static size_t	_get_str_len(int n, char *base)
{
	size_t			str_len;
	const size_t	base_len = ft_strlen(base);

	if (n == 0)
		return (1);
	str_len = 0;
	if (n < 0)
		str_len++;
	while (n != 0)
	{
		n /= base_len;
		str_len++;
	}
	return (str_len);
}

char	*ft_xitoa_base(int n, char *base)
{
	char	*str;
	size_t	str_len;

	str_len = _get_str_len(n, base);
	str = (char *)ft_xcalloc(str_len + 1, sizeof(char));
	_get_str_recursive(str, str_len - 1, n, base);
	return (str);
}
