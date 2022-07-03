/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:30:33 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 13:42:35 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	after_cd(void)
{
	char	path[PATH_MAX];
	char	*str;

	if (get_env_body("PWD"))
	{
		str = ft_xstrjoin("OLDPWD=", get_env_body("PWD"));
		add_env(str);
		free(str);
	}
	ft_memset(path, 0, PATH_MAX);
	if (!getcwd(path, sizeof(path)))
	{
		perror("getcwd");
		return ;
	}
	str = ft_xstrjoin("PWD=", path);
	add_env(str);
	free(str);
}

int	cd_home(void)
{
	char	*home;
	int		ret;

	home = get_env_body("HOME");
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	ret = chdir(home);
	if (ret != 0)
	{
		ft_dprintf_x(2, "minishell: cd: %s: %s\n", home, strerror(errno));
		return (1);
	}
	after_cd();
	return (0);
}

int	builtin_cd(t_word *word)
{
	int		ret;

	if (word->next == NULL)
		return (cd_home());
	ret = chdir(word->next->str);
	if (ret != 0)
	{
		ft_dprintf_x(2, "minishell: cd: %s: %s\n",
			word->next->str, strerror(errno));
		return (1);
	}
	after_cd();
	return (0);
}
