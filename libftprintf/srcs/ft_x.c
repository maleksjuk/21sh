/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:29:44 by obanshee          #+#    #+#             */
/*   Updated: 2019/11/29 20:54:10 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_x(t_printf **p)
{
	return (ft_x_universe(p, 'a', 'x'));
}

int		ft_x2(t_printf **p)
{
	return (ft_x_universe(p, 'A', 'X'));
}
