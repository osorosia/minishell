/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xspec_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:27:19 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 20:51:17 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*xspec_s(va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (str == NULL)
		return (ft_xstrdup("(null)"));
	return (ft_xstrdup(str));
}
