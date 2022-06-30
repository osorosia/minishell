/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:23:13 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 07:42:35 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_abs(int n)
{
	if (n < 0)
		return (-1 * n);
	return (n);
}

static void	_get_str_recursive(char *str, size_t str_i, int n)
{
	if (n < 0)
		str[0] = '-';
	str[str_i] = _abs(n % 10) + '0';
	if (n / 10 != 0)
		_get_str_recursive(str, str_i - 1, _abs(n / 10));
}

static size_t	_get_str_len(int n)
{
	size_t	str_len;

	if (n == 0)
		return (1);
	str_len = 0;
	if (n < 0)
		str_len++;
	while (n != 0)
	{
		n /= 10;
		str_len++;
	}
	return (str_len);
}

char	*ft_xitoa(int n)
{
	char	*str;
	size_t	str_len;

	str_len = _get_str_len(n);
	str = (char *)ft_xmalloc(sizeof(char) * (str_len + 1));
	_get_str_recursive(str, str_len - 1, n);
	str[str_len] = '\0';
	return (str);
}
