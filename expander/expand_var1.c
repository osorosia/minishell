/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:17:31 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 10:33:15 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*_get_var_name(char *str)
{
	char	*name;
	long	len;

	len = 0;
	while (str[len])
	{
		if (len == 0 && !is_var_name_char(str[len]))
			break ;
		else if (!is_var_name_char(str[len]))
			break ;
		len++;
	}
	name = ft_xstrndup(str, len);
	return (name);
}

long	_expand_var_at_doller_mark(char *str, char **new, long i)
{
	char	*name;
	char	*body;

	i++;
	if (str[i] == '?')
	{
		*new = ft_xstrjoin_with_free(*new, true, ft_xitoa(g_shell->sts), true);
		i++;
	}
	else if (!is_var_name_char_1st(str[i]))
		*new = ft_xstrjoin_with_free(*new, true, "$", false);
	else
	{
		name = _get_var_name(&str[i]);
		if (name[0] != '\0')
		{
			body = get_env_body(name);
			*new = ft_xstrjoin_with_free(*new, true, body, false);
			i += ft_strlen(name);
		}
		free(name);
	}
	return (i);
}
