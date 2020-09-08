/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:02:02 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/06 17:02:02 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t j;
	size_t k;

	k = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (k < len && haystack[k])
	{
		j = 0;
		while (needle[j] && haystack[k] && \
				needle[j] == haystack[k] && k++ < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[k - j]);
		k = k - j + 1;
	}
	return (0);
}
