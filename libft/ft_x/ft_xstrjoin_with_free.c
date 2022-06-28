/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrjoin_with_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:53:31 by rnishimo          #+#    #+#             */
/*   Updated: 2022/05/30 00:54:52 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xstrjoin_with_free(char *s1, bool b1, char *s2, bool b2)
{
	char	*str;

	str = ft_xstrjoin(s1, s2);
	if (b1)
		free(s1);
	if (b2)
		free(s2);
	return (str);
}
