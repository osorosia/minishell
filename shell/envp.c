/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:18:40 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:20:11 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	_get_env_size(void)
{
	long	sz;
	t_env	*env;


	sz = 0;
	env = g_shell->env;
	while (env)
	{
		if (env->body)
			sz++;
		env = env->next;
	}
	return (sz);
}

char	**create_envp(void)
{
	char		**envp;
	t_env		*env;
	long		i;
	const long	sz = _get_env_size();

	envp = ft_xcalloc(sz + 1, sizeof(char *));
	env = g_shell->env;
	i = 0;
	while (env)
	{
		if (env->body)
		{
			envp[i] = ft_xstrjoin(env->name, "=");
			envp[i] = ft_xstrjoin_with_free(envp[i], true, env->body, false);
			i++;
		}
		env = env->next;
	}
	return (envp);
}

void	free_envp(char **envp)
{
	long	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i++]);
	}
	free(envp);
}
