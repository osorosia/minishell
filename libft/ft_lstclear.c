/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:21:36 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/13 06:28:57 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst_next;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		lst_next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lst_next;
	}
}
