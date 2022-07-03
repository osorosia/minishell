/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:22:28 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 13:42:04 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_sigint_heredoc(int signal)
{
	(void)signal;
	g_shell->interrupt = true;
	g_shell->sts = 1;
	close(0);
	ft_putstr_fd("\n", 2);
}

void	signal_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, _sigint_heredoc);
}
