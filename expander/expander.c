/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:23:19 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 15:23:36 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander(t_node *node)
{
	expand_var(node);
	split_space(node);
	delete_quote(node);
	generate_pathname(node);
}

void	expander_for_debug(t_node *node)
{
	expand_var_for_debug(node);
	debug_expander(node, "expand_var");
	split_space_for_debug(node);
	debug_expander(node, "split_space");
	delete_quote_for_debug(node);
	debug_expander(node, "delete_quote");
	generate_pathname_for_debug(node);
	debug_expander(node, "generate_pathname");
}
