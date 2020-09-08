/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:11:13 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/12 13:11:14 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len-- != 0)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}
