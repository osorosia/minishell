/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_dup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:57:02 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 11:05:53 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	x_dup(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
	{
		perror("dup");
		exit(1);
	}
	return (new_fd);
}

int	x_dup2(int fd1, int fd2)
{
	int	new_fd;

	new_fd = dup2(fd1, fd2);
	if (new_fd == -1)
	{
		perror("dup");
		exit(1);
	}
	return (new_fd);
}
