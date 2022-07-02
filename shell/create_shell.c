/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:14:57 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 18:01:23 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	*create_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_xcalloc(1, sizeof(t_shell));
	shell->env = create_env(envp);
	shell->fd_stdout = dup(1);
	shell->fd_stdin = dup(0);
	return (shell);
}
