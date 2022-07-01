/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:54:40 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 15:57:58 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_number(char *str)
{
	long	i;

	if (str[0] == '\0')
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		if (!ft_isdigit(str[i]))
			return (false);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_overflow(char *str)
{
	unsigned long	num;
	bool			minus;
	long			i;

	minus = false;
	num = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		minus = (str[i] == '-');
		i++;
	}
	while (str[i])
	{
		if ((num * 10 + str[i] - '0') / 10 != num)
		{
			return (false);
		}
		num = num * 10 + str[i] - '0';
		if (num > (unsigned long)LONG_MAX + minus)
			return (false);
		i++;
	}
	return (true);
}

int	_atoi(char *str)
{
	long	sign;
	long	num;
	long	i;

	sign = 1;
	num = 0;
	i = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		num = 10 * num + str[i] - '0';
		i++;
	}
	return (sign * num);
}

bool	_is_too_many_arguments(t_word *word)
{
	return (word->next->next != NULL);
}

int	exec_exit(t_word *word)
{
	if (word->next == NULL)
		exit(g_shell->sts);
	if (!is_number(word->next->str)
		|| !check_overflow(word->next->str))
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
			word->next->str);
		exit(255);
	}
	if (_is_too_many_arguments(word))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit(_atoi(word->next->str));
	return (0);
}
