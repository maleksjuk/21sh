/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:33:23 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/05 19:13:39 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*ptr;
	size_t		len;

	len = ft_strlen(needle);
	ptr = haystack;
	if (*needle == '\0')
		return (char *)ptr;
	while ((ptr = ft_strchr(ptr, *needle)) != 0)
	{
		if (ft_strncmp(ptr, needle, len) == 0)
			return (char *)ptr;
		ptr++;
	}
	return (0);
}
