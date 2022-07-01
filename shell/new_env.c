/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:20:57 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:21:08 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_env(char *name, char *body)
{
	t_env	*env;

	env = ft_xcalloc(1, sizeof(t_env));
	env->name = name;
	env->body = body;
	return (env);
}
