/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:51:27 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/06 17:51:28 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *p;
	char *end;

	end = NULL;
	p = NULL;
	if (c == '\0')
		return (ft_strchr(s, '\0'));
	while ((p = ft_strchr(s, c)) != NULL)
	{
		end = p;
		s = p + 1;
	}
	return ((char *)end);
}
