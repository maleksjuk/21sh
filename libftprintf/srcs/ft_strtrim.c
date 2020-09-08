/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:06:22 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/11 19:06:23 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		k;
	int		len;
	char	*dest;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	k = i;
	while (s[i + 1] != '\0')
		i++;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i--;
	len = i - k + 1;
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (len-- != 0)
		dest[i++] = s[k++];
	dest[i] = '\0';
	return (dest);
}
