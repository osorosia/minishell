/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xclose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:47:26 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 08:18:27 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_xclose(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret != 0)
	{
		perror("close");
		exit(1);
	}
	return (ret);
}
