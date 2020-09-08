/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:17:17 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/12 18:17:18 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*link;
	t_list		*new_lst;

	if (!lst || !f)
		return (NULL);
	new_lst = f(lst);
	link = new_lst;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new_lst->next = f(lst)))
		{
			free(new_lst->next);
			return (NULL);
		}
		new_lst = new_lst->next;
	}
	return (link);
}
