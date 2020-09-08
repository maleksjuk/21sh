/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:54:04 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/09 18:54:58 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char *tp;
	char *fp;
	char ch;

	ch = c;
	fp = (char *)src;
	tp = dst;
	if (n != 0)
	{
		if ((*tp++ = *fp++) == ch)
			return ((void *)tp);
		while (--n != 0)
		{
			if ((*tp++ = *fp++) == ch)
				return ((void *)tp);
		}
	}
	return (0);
}
