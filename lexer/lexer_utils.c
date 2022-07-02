/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:53:25 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:46:36 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*skip(t_token *tok, t_token_kind kind, char *str)
{
	if (tok->kind != kind)
		syntax_error(tok->str, tok->len);
	if (str != NULL
		&& (tok->len != ft_strlen(str)
			|| ft_strncmp(tok->str, str, tok->len) != 0))
		syntax_error(tok->str, tok->len);
	return (tok->next);
}

bool	equal(t_token *tok, t_token_kind kind, char *str)
{
	if (tok->kind != kind)
		return (false);
	if (str != NULL
		&& (tok->len != ft_strlen(str)
			|| ft_strncmp(tok->str, str, tok->len) != 0))
		return (false);
	return (true);
}
