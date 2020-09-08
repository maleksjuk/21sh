/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:04:59 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/04 15:54:04 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_check_rounding(long double num, long double *x, int precision)
{
	int i;

	i = 0;
	num *= 10;
	if (precision == 0 && ((intmax_t)num >= 5 || (intmax_t)num <= -5))
		(*x) = ((*x) < 0) ? (*x) - 1 : (*x) + 1;
	else if ((int)num == 9 || (int)num <= -9)
	{
		while (i < precision)
		{
			if (num >= 9 || num <= -9)
				num = (num - (int)(num)) * 10;
			else
				break ;
			i++;
		}
		if ((num > 5 || num < -5) && i == precision)
			(*x) = ((*x) < 0) ? (*x) - 1 : (*x) + 1;
	}
	return (0);
}

void	ft_left_part(long double *num, char **str, int *i, t_printf **p)
{
	intmax_t	x;
	intmax_t	modulo;

	x = 0;
	modulo = (intmax_t)ft_modulo(*num);
	while ((int)*num != 0)
	{
		x = x + ((intmax_t)(*num / modulo)) * (intmax_t)modulo;
		*num -= (intmax_t)(*num / modulo) * modulo;
		modulo /= 10;
	}
	modulo = (intmax_t)ft_modulo(x);
	while (modulo != 0)
	{
		(*str)[(*i)++] = (char)(x / (intmax_t)modulo) + 48;
		x -= (x / (intmax_t)modulo) * (intmax_t)modulo;
		modulo /= 10;
	}
	if ((*p)->precision != 0 || (((*p)->hash) && (*p)->precision == 0))
		(*str)[(*i)++] = '.';
	ft_right_part(str, i, *num, (*p)->precision);
}

int		ft_infinity(t_printf **p, double num)
{
	if (num == DBL_MAX)
		ft_dbl_big(p);
	else if (num == 1 / -0.0)
		(*p)->str_val = ((*p)->uppercase == 1) ?
				ft_strdup("-Inf\0") : ft_strdup("-inf\0");
	else if (num == 1 / 0.0 && (*p)->space && !(*p)->plus)
		(*p)->str_val = ((*p)->uppercase == 1) ?
				ft_strdup(" Inf\0") : ft_strdup(" inf\0");
	else if (num == 1 / 0.0 && (*p)->plus)
		(*p)->str_val = ((*p)->uppercase == 1) ?
				ft_strdup("+Inf\0") : ft_strdup("+inf\0");
	else if (num == 1 / 0.0 && !(*p)->plus)
		(*p)->str_val = ((*p)->uppercase == 1) ?
				ft_strdup("Inf\0") : ft_strdup("inf\0");
	else if (num != num)
		(*p)->str_val = ((*p)->uppercase == 1) ?
				ft_strdup("Nan\0") : ft_strdup("nan\0");
	else
		return (0);
	(*p)->double_val = 1;
	ft_s(p);
	free((*p)->str_val);
	return (1);
}

int		ft_inf_prec_flags(t_printf **p, int *tab3, long double num)
{
	if (ft_infinity(p, num))
		return (1);
	if ((*p)->precision == -1)
		(*p)->precision = 6;
	if (num < 0 || (*p)->plus || (*p)->space || (*p)->minus)
		*tab3 = 1;
	return (0);
}

int		ft_f(t_printf **p)
{
	int			tab[4];
	char		*str;
	char		*str1;
	long double	num;

	tab[2] = 0;
	tab[3] = 0;
	num = (*p)->double_val;
	if (ft_inf_prec_flags(p, &tab[3], num))
		return (1);
	ft_check_rounding((num - (intmax_t)(num)), &num, (*p)->precision);
	tab[0] = len_nbr((intmax_t)num);
	tab[1] = max_val((*p)->precision, (*p)->width) + tab[3] + tab[0];
	if (!(str = ft_strnew(tab[1] + 1)))
		return (1);
	tab[2] = ft_flags(p, &num, str, tab);
	(!(*p)->minus) ? ft_left_part(&num, &str, &tab[2], p) : 0;
	(*p)->final_len += ft_strlen(str);
	str1 = (*p)->final_str;
	(*p)->final_str = ft_strjoin_len((*p)->final_str, str, ft_strlen(str),
		(*p)->final_len - ft_strlen(str));
	free(str);
	free(str1);
	return (0);
}
