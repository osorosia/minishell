/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:45:29 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/11 17:38:03 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	i = 0;
	if (p_dest < p_src)
	{
		while (i < n)
		{
			p_dest[i] = p_src[i];
			i++;
		}
	}
	else
	{
		while (i++ < n)
			p_dest[n - i] = p_src[n - i];
	}
	return (dest);
}
