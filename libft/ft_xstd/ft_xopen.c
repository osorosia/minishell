/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xopen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:53:31 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/30 01:54:36 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_xopen(const char *path, int oflag)
{
	int	fd;

	fd = open(path, oflag);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}
