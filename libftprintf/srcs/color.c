/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:47:31 by obanshee          #+#    #+#             */
/*   Updated: 2019/11/24 14:47:39 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	pts(char *s, int c)
{
	while (*s)
		write(1, s++, 1);
	ft_putnbr(c);
	write(1, "m", 1);
}

int		ft_init_color(char **format, int color, int len, int i)
{
	pts("\x1b[", color);
	(*format) = (*format + len + i);
	return (0);
}

int		ft_set_color(char **format, int i)
{
	if (ft_strncmp((const char *)(*format + i), "{red}", 5) == 0)
		return (ft_init_color(format, 91, 5, i));
	else if (ft_strncmp((const char *)(*format + i), "{green}", 7) == 0)
		return (ft_init_color(format, 92, 7, i));
	else if (ft_strncmp((const char *)(*format + i), "{yellow}", 8) == 0)
		return (ft_init_color(format, 93, 8, i));
	else if (ft_strncmp((const char *)(*format + i), "{blue}", 6) == 0)
		return (ft_init_color(format, 94, 6, i));
	else if (ft_strncmp((const char *)(*format + i), "{magenta}", 9) == 0)
		return (ft_init_color(format, 95, 9, i));
	else if (ft_strncmp((const char *)(*format + i), "{cyan}", 6) == 0)
		return (ft_init_color(format, 96, 6, i));
	else if (ft_strncmp((const char *)(*format + i), "{white}", 7) == 0)
		return (ft_init_color(format, 97, 7, i));
	else if (ft_strncmp((const char *)(*format + i), "{eoc}", 5) == 0)
		return (ft_init_color(format, 0, 5, i));
	else
		return (i);
}
