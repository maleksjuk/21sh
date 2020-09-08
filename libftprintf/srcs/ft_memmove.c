/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:59:19 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/08 17:59:20 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *ptrd;
	char *ptrs;
	char *ptends;
	char *ptendd;

	ptrd = dst;
	ptrs = (char *)src;
	if (ptrd < ptrs)
		while (len-- != 0)
			*ptrd++ = *ptrs++;
	else
	{
		ptends = ptrs + (len - 1);
		ptendd = ptrd + (len - 1);
		while (len--)
			*ptendd-- = *ptends--;
	}
	return (dst);
}
