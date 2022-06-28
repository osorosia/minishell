/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:24:36 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/28 19:24:52 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_base_fd(size_t num, char *base, int fd)
{
	const long	base_len = ft_strlen(base);

	if (num / base_len != 0)
		ft_putunbr_base_fd(num / base_len, base, fd);
	ft_putchar_fd(base[num % base_len], 1);
}
