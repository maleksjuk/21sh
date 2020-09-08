/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:18:50 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/08 19:18:52 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*ptrd;
	const char	*s;
	size_t		lend;
	size_t		num;

	s = src;
	ptrd = dst;
	num = size;
	while (num-- != 0 && *ptrd != '\0')
		ptrd++;
	lend = ptrd - dst;
	num = size - lend;
	if (num == 0)
		return (lend + ft_strlen(s));
	while (*s != '\0')
	{
		if (num != 1)
		{
			*ptrd++ = *s;
			num--;
		}
		s++;
	}
	*ptrd = '\0';
	return (lend + (s - src));
}
