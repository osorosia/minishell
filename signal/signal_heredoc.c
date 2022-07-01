/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:22:28 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:59:50 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO
void	_sigint_heredoc(int signal)
{
	g_shell->interrupt = true;
}

void	signal_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, _sigint_heredoc);
}
