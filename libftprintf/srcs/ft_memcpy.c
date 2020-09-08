/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:29:52 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/08 16:29:53 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptrd;
	const char	*ptrs;

	ptrd = dst;
	ptrs = src;
	while (n-- != 0)
		ptrd[n] = ptrs[n];
	return (dst);
}
