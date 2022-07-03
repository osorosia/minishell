/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signai_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:22:03 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 13:41:53 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_sigint_exec(int signal)
{
	(void)signal;
	g_shell->interrupt = true;
	ft_putstr_fd("\n", 2);
}

void	signal_exec(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, _sigint_exec);
}
