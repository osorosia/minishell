/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:12:45 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:05:05 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_add_env_main(char *name, char *body)
{
	t_env	*env;

	env = g_shell->env;
	while (true)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(name);
			if (body)
			{
				free(env->body);
				env->body = body;
			}
			return ;
		}
		if (env->next == NULL)
		{
			env->next = new_env(name, body);
			return ;
		}
		env = env->next;
	}
}

// str: "name=body" or "name"
void	add_env(char *str)
{
	char	*name;
	char	*body;

	name = create_env_name(str);
	body = create_env_body(str);
	if (g_shell->env == NULL)
	{
		g_shell->env = new_env(name, body);
		return ;
	}
	_add_env_main(name, body);
}

void	_add_env_plus_main(char *name, char *body)
{
	t_env	*env;

	env = g_shell->env;
	while (true)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(name);
			env->body = ft_xstrjoin_with_free(env->body, true, body, true);
			return ;
		}
		if (env->next == NULL)
		{
			env->next = new_env(name, body);
			return ;
		}
		env = env->next;
	}
}

// str: "name+=body"
void	add_env_plus(char *str)
{
	char	*name;
	char	*body;

	name = create_env_name_plus(str);
	body = create_env_body_plus(str);
	if (g_shell->env == NULL)
	{
		g_shell->env = new_env(name, body);
		return ;
	}
	_add_env_plus_main(name, body);
}
