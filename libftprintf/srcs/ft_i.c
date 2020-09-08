/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 20:50:24 by obanshee          #+#    #+#             */
/*   Updated: 2019/11/29 20:50:40 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

long double	ft_len_pow(long double num, int k, int precision)
{
	if (len_nbr((intmax_t)(num)) + k == precision)
		return (ft_modulo(num) * ft_pow(k));
	else
		return (ft_modulo(num) * ft_pow(k) / 10);
}

int			ft_i(t_printf **p)
{
	return (ft_d(p));
}
