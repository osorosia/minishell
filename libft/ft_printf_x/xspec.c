/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xspec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:25:52 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 20:56:20 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*xspec(va_list ap, char c)
{
	if (c == 's')
		return (xspec_s(ap));
	if (c == 'd')
		return (xspec_d(ap));
	if (c == '%')
		return (ft_xstrdup("%"));
	return (NULL);
}
