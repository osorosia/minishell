/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:54:00 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 15:54:30 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_env(t_word *word)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		if (env->body)
			ft_printf("%s=%s\n", env->name, env->body);
		env = env->next;
	}
	return (0);
}
