/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:59:13 by rnishimo          #+#    #+#             */
/*   Updated: 2021/11/13 07:08:16 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_map;
	t_list	*lst_map_now;
	t_list	*lst_map_back;

	lst_map = NULL;
	lst_map_back = NULL;
	while (lst)
	{
		if (f)
			lst_map_now = ft_lstnew((*f)(lst->content));
		else
			lst_map_now = ft_lstnew(lst->content);
		if (lst_map_now == NULL)
		{
			ft_lstclear(&lst_map, del);
			return (NULL);
		}
		if (lst_map == NULL)
			lst_map = lst_map_now;
		if (lst_map_back != NULL)
			lst_map_back->next = lst_map_now;
		lst_map_back = lst_map_now;
		lst = lst->next;
	}
	return (lst_map);
}
