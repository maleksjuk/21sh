/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:51:44 by obanshee          #+#    #+#             */
/*   Updated: 2019/11/29 20:44:37 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	max_val(int a, int b)
{
	return (a > b ? a : b);
}

int	len_nbr(intmax_t num)
{
	int	len;

	len = 1;
	if (num > 9 || num < -9)
	{
		len++;
		num /= 10;
	}
	if (num < 0)
		num *= -1;
	while (num > 9)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

int	len_nbr_u(uintmax_t num)
{
	int	len;

	len = 1;
	while (num > 9)
	{
		num = num / 10;
		len++;
	}
	return (len);
}
