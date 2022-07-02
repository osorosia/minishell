/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:07:28 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:15:25 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*_new_node_stmt(t_node_kind kind, t_node *pipe_cmd_node)
{
	t_node	*node;

	node = ft_xcalloc(1, sizeof(t_node));
	node->kind = kind;
	node->lhs = pipe_cmd_node;
	return (node);
}

void	_add_node_stmt(t_node *node, t_node_kind kind, t_node *bracket_node)
{
	while (node->rhs)
		node = node->rhs;
	node->rhs = _new_node_stmt(kind, bracket_node);
}

void	*_new_node_bracket(t_node *stmt_node)
{
	t_node	*node;

	node = ft_xcalloc(1, sizeof(t_node));
	node->kind = ND_BRACKET;
	node->lhs = stmt_node;
	return (node);
}

t_node	*_new_node_pipe(t_node *cmd_node)
{
	t_node	*node;

	node = ft_xcalloc(1, sizeof(t_node));
	node->kind = ND_PIPE;
	node->rhs = cmd_node;
	return (node);
}

t_node	*_add_node_pipe(t_node *node, t_node *cmd_node)
{
	t_node	*new;

	new = _new_node_pipe(cmd_node);
	new->lhs = node;
	return (new);
}
