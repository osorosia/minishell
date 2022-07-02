/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:58:18 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 20:58:24 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_envs(void)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		if (env->body)
			ft_printf_x("declare -x %s=\"%s\"\n", env->name, env->body);
		else
			ft_printf_x("declare -x %s\n", env->name);
		env = env->next;
	}
}

bool	validate_name(char *str)
{
	long	i;

	if (ft_strncmp(str, "+=", 2) == 0 || str[0] == '=')
		return (false);
	i = 0;
	while (str[i] && str[i] != '=' && (str[i] != '+' || str[i + 1] != '='))
	{
		if (i == 0 && ft_isdigit(str[i]))
			return (false);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	exec_export(t_word *word)
{
	int	ret;

	ret = 0;
	if (word->next == NULL)
	{
		show_envs();
		return (0);
	}
	word = word->next;
	while (word)
	{
		if (!validate_name(word->str))
		{
			ft_dprintf_x(2, "minishell: export: `%s': not a valid identifier\n",
				word->str);
			ret = 1;
		}
		else if (ft_strnstr(word->str, "+=", ft_strlen(word->str)))
			add_env_plus(word->str);
		else
			add_env(word->str);
		word = word->next;
	}
	return (ret);
}
