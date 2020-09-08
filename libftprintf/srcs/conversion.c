/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 20:43:56 by obanshee          #+#    #+#             */
/*   Updated: 2019/11/29 20:44:47 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	transform(uintmax_t num, unsigned int system, char dec, char *str)
{
	char	c;
	int		i;

	if (num < system)
	{
		if (num > 9)
			c = num - 10 + dec;
		else
			c = num + '0';
		str[0] = c;
		return (0);
	}
	else
	{
		i = transform(num / system, system, dec, str) + 1;
		if (num % system <= 9)
			c = num % system + '0';
		else
			c = num % system - 10 + dec;
		str[i] = c;
		return (i);
	}
}

int	simvol_out(t_printf **p, int len, char c, char *str)
{
	int	i;

	i = 0;
	while ((*p)->width > len)
	{
		str[i++] = c;
		((*p)->width)--;
	}
	return (i);
}

int	for_precision(t_printf **p, int len, char *str)
{
	int	i;

	i = 0;
	while ((*p)->precision > len)
	{
		str[i++] = '0';
		((*p)->precision)--;
		if ((*p)->width > 0)
			((*p)->width)--;
	}
	return (i);
}
