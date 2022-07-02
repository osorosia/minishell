/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:40:29 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:45:09 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(char *str, long len)
{
	char	*print_str;

	print_str = ft_xstrndup(str, len);
	ft_dprintf_x(
		2, "minishell: syntax error near unexpected token `%s'\n", print_str);
	free(print_str);
	exit(1);
}
