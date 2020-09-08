/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:50:34 by pguitar           #+#    #+#             */
/*   Updated: 2019/04/06 14:50:36 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		ft_over(const char *str, long int x)
{
	if (str[0] == '-' && x > 0)
		return (0);
	else if ((str[0] == '+' || (str[0] <= '9' && str[0] >= '0')) && x < 0)
		return (-1);
	return ((int)x);
}

int				ft_atoi(const char *str)
{
	int			i;
	long int	x;

	x = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+')
	{
		i++;
		while (str[i] <= '9' && str[i] >= '0')
			x = x * 10 + (str[i++] - '0');
	}
	else if (str[i] == '-')
	{
		i++;
		while (str[i] <= '9' && str[i] >= '0')
			x = x * 10 + (str[i++] - '0');
		x = -x;
	}
	else
		while (str[i] <= '9' && str[i] >= '0')
			x = x * 10 + (str[i++] - '0');
	return (ft_over(str, x));
}
