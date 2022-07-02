/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:54:00 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:53:53 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_word *word)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		if (env->body)
			ft_printf_x("%s=%s\n", env->name, env->body);
		env = env->next;
	}
	return (0);
}
