/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:11:45 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/03 18:57:44 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putstr_len(char const *s, int len)
{
	int i;

	i = 0;
	if (s)
		while (i < len)
			ft_putchar(s[i++]);
}

char	*ft_strjoin_len(char const *s1, char const *s2, int len_str,
						int len_fin)
{
	int		i;
	int		len;
	char	*dest;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	len = len_fin + len_str;
	if (!(dest = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (++i < len_fin)
		dest[i] = s1[i];
	len = 0;
	while (len < len_str)
		dest[i++] = s2[len++];
	dest[i] = '\0';
	return (dest);
}

void	ft_free(char *str1, char *str2)
{
	free(str1);
	free(str2);
}
