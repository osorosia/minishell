/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:41:55 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:51:55 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_opt_n(char *str)
{
	long	i;

	if (ft_strncmp(str, "-n", 2) != 0)
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	builtin_echo(t_word *word)
{
	bool	opt_n;
	t_word	*w;

	opt_n = false;
	w = word->next;
	while (w && is_opt_n(w->str))
	{
		opt_n = true;
		w = w->next;
	}
	while (w)
	{
		ft_putstr_fd(w->str, 1);
		w = w->next;
		if (w)
			ft_putstr_fd(" ", 1);
	}
	if (!opt_n)
		ft_putstr_fd("\n", 1);
	return (0);
}
