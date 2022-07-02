/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:01:50 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 23:53:47 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_word *word)
{
	word = word->next;
	while (word)
	{
		if (word->str)
			del_env(word->str);
		word = word->next;
	}
	return (0);
}
