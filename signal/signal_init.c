/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:22:47 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:23:09 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_sigint_init(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_shell->sts = 128 + SIGINT;
}

void	signal_init(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, _sigint_init);
	g_shell->interrupt = false;
}
