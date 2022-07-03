/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:26:05 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 11:37:42 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(t_node *node)
{
	t_cmd		*cmd;
	long		i;
	static	int	(*builtin_fn[])(t_word *) = {
		builtin_echo, builtin_cd, builtin_pwd, builtin_export,
		builtin_unset, builtin_env, builtin_exit, NULL};
	static char	*kw[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	cmd = node->cmd;
	i = 0;
	while (kw[i])
	{
		if (strcmp(kw[i], cmd->word->str) == 0)
		{
			g_shell->sts = builtin_fn[i](cmd->word);
			break ;
		}
		i++;
	}
	if (kw[i] == NULL)
		error("no match builtin");
}
