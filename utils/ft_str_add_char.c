/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_add_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:23:51 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:24:04 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_add_char(char *str, char c)
{
	char	ch[2];

	ch[0] = c;
	ch[1] = '\0';
	return (ft_xstrjoin_with_free(str, true, ch, false));
}
