/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 20:28:14 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/01 20:50:08 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

long double	ft_pow(int i)
{
	long double modulo;

	modulo = 1;
	while (i-- != 0)
		modulo *= 10;
	return (modulo);
}

long double	ft_modulo(long double num)
{
	long double modulo;

	modulo = 1;
	while ((intmax_t)(num /= 10) != 0)
		modulo *= 10;
	return (modulo);
}

void		ft_overload(char **str, int *i, long double *num, int *precision)
{
	int j;

	j = 0;
	if (*precision > 17)
	{
		while (j++ < 4)
		{
			(*num) = (*num) * 10;
			(*str)[(*i)++] = (char)((*num)) + 48;
			(*num) -= (intmax_t)((*num));
			(*precision)--;
		}
	}
}

void		ft_write_right_part(char **str, int *i, long double *num,
								long double *modulo)
{
	(*str)[(*i)++] = (char)(*num / *modulo) + 48;
	*num -= (intmax_t)(*num / *modulo) * (intmax_t)(*modulo);
	*modulo /= 10;
}

void		ft_right_part(char **str, int *i, long double num, int precision)
{
	int			k;
	int			j;
	long double	modulo;

	ft_overload(str, i, &num, &precision);
	j = 0;
	k = 0;
	num = (double)num;
	while (j++ < precision)
	{
		num = num * 10;
		if ((intmax_t)num == 0)
			if ((intmax_t)(num + 0.01) == 0)
				k++;
	}
	modulo = ft_modulo(num);
	if (num - (intmax_t)num >= 0.5)
		num++;
	if (ft_modulo(num) != modulo && k == 0)
		num = 0;
	modulo = ft_len_pow(num, k, precision);
	j = 0;
	while (j++ < precision)
		ft_write_right_part(str, i, &num, &modulo);
	(*str)[(*i)] = '\0';
}
