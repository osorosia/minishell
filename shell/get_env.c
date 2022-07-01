/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:20:25 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:20:52 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_body(char *name)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env->body);
		env = env->next;
	}
	return (NULL);
}
