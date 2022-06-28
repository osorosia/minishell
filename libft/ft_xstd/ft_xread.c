/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:54:45 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/30 01:56:53 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_xread(int fd, void *buf, size_t n)
{
	ssize_t	read_byte;

	read_byte = read(fd, buf, n);
	if (read_byte < 0)
	{
		perror("read");
		exit(1);
	}
	return (read_byte);
}
