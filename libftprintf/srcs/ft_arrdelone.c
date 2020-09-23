/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 02:25:42 by mcanal            #+#    #+#             */
/*   Updated: 2020/09/23 15:35:17 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** free a string from a string array
** the right side of the array will be moved consequently
*/

#include "libft.h"

void		ft_arrdelone(char **arr, char *to_del)
{
	while (*arr && *arr != to_del)
		arr++;
	if (!*arr)
		return ;
	ft_memdel((void *)&to_del);
	while ((*arr = *(arr + 1)))
		arr++;
}
