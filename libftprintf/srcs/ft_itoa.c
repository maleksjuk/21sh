/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:16:44 by pguitar           #+#    #+#             */
/*   Updated: 2019/12/02 14:08:52 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	char	*get_num(intmax_t n, int len)
{
	char *str;

	if (!(str = (char *)malloc(sizeof(*str) * len + 2)))
		return (NULL);
	str[len + 1] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (n != 0)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

char			*ft_itoa(intmax_t n)
{
	int			len;
	intmax_t	n_len;

	len = 0;
	if (n < 0)
		n = -n;
	n_len = n;
	while (n_len /= 10)
		len++;
	return (get_num(n, len));
}
