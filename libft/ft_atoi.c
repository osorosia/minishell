/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:00:02 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/21 23:32:55 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	_isspace(int c)
{
	return (c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' ');
}

static bool	_is_overflow(const char *s, long long num, long long sign)
{
	long long	div;
	long long	mod;

	div = LONG_MAX / 10;
	mod = LONG_MAX % 10;
	if (sign == -1)
	{
		mod++;
		if (mod == 10)
		{
			div++;
			mod = 0;
		}
	}
	return (num > div || (num == div && *s - '0' > mod));
}

static long	long	_atoll(const char *s, long long num, long long sign)
{
	while (ft_isdigit(*s))
	{
		if (_is_overflow(s, num, sign))
		{
			if (sign == -1)
				return (LONG_MIN);
			else
				return (LONG_MAX);
		}
		num = num * 10 + *s - '0';
		s++;
	}
	num *= sign;
	return (num);
}

int	ft_atoi(const char *s)
{
	long long	num;
	long long	sign;

	num = 0;
	sign = 1;
	while (_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	return ((int)_atoll(s, num, sign));
}
