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

static long	long	_atoll(const char *s, long long num, long long sign)
{
	while (ft_isdigit(*s))
	{
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
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
		sign *= -1;
	if (*s == '+' || *s == '-')
		s++;
	return ((int)_atoll(s, num, sign));
}
