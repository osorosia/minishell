/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starts_with.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:24:37 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 16:24:49 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	starts_with(const char *dest, const char *src)
{
	const size_t	len = ft_strlen(src);

	return (ft_strncmp(dest, src, len) == 0);
}
