/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:01:32 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 13:43:08 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(t_word *word)
{
	char	cwd[PATH_MAX];

	(void)word;
	ft_memset(cwd, 0, PATH_MAX);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		return (0);
	}
	ft_putendl_fd(cwd, 1);
	return (0);
}
