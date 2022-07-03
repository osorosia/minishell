/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_pathname1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:23:46 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 10:39:48 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_paths(char **paths)
{
	long	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

bool	check_pathname(char *pathname)
{
	struct stat	st;

	if (access(pathname, F_OK) != 0)
		return (false);
	if (stat(pathname, &st) != 0)
		return (false);
	return (!S_ISDIR(st.st_mode));
}

char	*find_pathname(char *str)
{
	char	**paths;
	char	*base;
	char	*pathname;
	long	i;

	paths = ft_xsplit(get_env_body("PATH"), ':');
	if (paths == NULL)
		return (ft_xstrdup(str));
	i = 0;
	while (paths[i])
	{
		base = ft_xstrjoin(paths[i], "/");
		pathname = ft_xstrjoin_with_free(base, true, str, false);
		if (check_pathname(pathname))
		{
			free_paths(paths);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	free_paths(paths);
	return (NULL);
}
