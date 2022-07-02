/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_pathname.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:23:46 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 20:07:12 by rnishimo         ###   ########.fr       */
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

	paths = ft_split(get_env_body("PATH"), ':');
	if (paths == NULL)
	{
		str = ft_xstrdup(str);
		return (str);
	}
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

char	*get_pathname_str(char *str)
{
	char	*pathname;

	if (ft_strchr(str, '/'))
		pathname = ft_xstrdup(str);
	else
		pathname = find_pathname(str);
	return (pathname);
}

void	generate_pathname(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == ND_STMT)
		return ;
	if (node->kind == ND_CMD)
	{
		if (node->cmd->word == NULL)
			return ;
		if (is_builtin(node->cmd->word->str))
			node->cmd->is_builtin = true;
		else
			node->cmd->pathname = get_pathname_str(node->cmd->word->str);
	}
	else
	{
		generate_pathname(node->lhs);
		generate_pathname(node->rhs);
	}
}
