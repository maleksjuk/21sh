/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:23:12 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/12 17:23:13 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*lst;
	t_list	*new_lst;

	if (del != NULL && *alst != NULL)
	{
		lst = *alst;
		while (lst)
		{
			new_lst = lst->next;
			(*del)(lst->content, lst->content_size);
			free(lst);
			lst = new_lst;
		}
		*alst = NULL;
	}
}
