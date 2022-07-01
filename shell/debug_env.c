/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:15:17 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:15:33 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	debug_env(void)
{
	t_env	*env;

	env = g_shell->env;
	fprintf(stderr, "env {\n");
	while (env)
	{
		print_indent(INDENT);
		fprintf(stderr, "%s", env->name);
		if (env->body)
			fprintf(stderr, "=%s", env->body);
		fprintf(stderr, "\n");
		env = env->next;
	}
	fprintf(stderr, "}\n\n");
}
