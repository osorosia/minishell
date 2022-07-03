/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:23:19 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 14:03:07 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander(t_node *node)
{
	expand_var(node);
	split_space(node);
	expand_asterisk(node);
	delete_quote(node);
	generate_pathname(node);
}
