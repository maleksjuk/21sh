/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:06:59 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/12 15:06:59 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memalloc(size_t size)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	if (!(str = (unsigned char *)malloc(sizeof(unsigned char) * size)))
		return (NULL);
	while (size-- != 0)
		str[i++] = 0;
	return ((void *)str);
}
