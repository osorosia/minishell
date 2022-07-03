/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 10:29:01 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 10:32:49 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_var_name_char_1st(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_var_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
