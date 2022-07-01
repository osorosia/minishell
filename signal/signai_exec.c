/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signai_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:22:03 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:22:19 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_sigint_exec(int signal)
{
	g_shell->interrupt = true;
	ft_putstr_fd("\n", 2);
}

void	signal_exec(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, _sigint_exec);
}
