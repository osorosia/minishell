/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_pathname.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:23:46 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 10:35:51 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_pathname(char *str);

char	*get_pathname_str(char *str)
{
	char	*pathname;

	if (ft_strchr(str, '/'))
		pathname = ft_xstrdup(str);
	else
		pathname = find_pathname(str);
	return (pathname);
}

void	generate_pathname(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->kind == ND_STMT)
		return ;
	if (node->kind == ND_CMD)
	{
		if (node->cmd->word == NULL)
			return ;
		if (is_builtin(node->cmd->word->str))
			node->cmd->is_builtin = true;
		else
			node->cmd->pathname = get_pathname_str(node->cmd->word->str);
	}
	else
	{
		generate_pathname(node->lhs);
		generate_pathname(node->rhs);
	}
}
