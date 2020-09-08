/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:05:22 by obanshee          #+#    #+#             */
/*   Updated: 2019/11/29 21:03:34 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_uint_value(t_printf **p)
{
	uintmax_t val;

	if ((*p)->size == 'H')
		val = (unsigned char)(va_arg((*p)->ap, unsigned int));
	else if ((*p)->size == 'h')
		val = (unsigned short int)(va_arg((*p)->ap, unsigned int));
	else if ((*p)->size == 'L')
		val = (unsigned long long int)(va_arg((*p)->ap,
			unsigned long long int));
	else if ((*p)->size == 'l')
		val = (unsigned long int)(va_arg((*p)->ap, unsigned long int));
	else if ((*p)->type == 'p')
		val = (uintmax_t)(va_arg((*p)->ap, uintmax_t));
	else
		val = (unsigned int)va_arg((*p)->ap, unsigned int);
	(*p)->uint_val = (uintmax_t)val;
}

void	ft_int_value(t_printf **p)
{
	intmax_t val;

	if ((*p)->size == 'H')
		val = (signed char)(va_arg((*p)->ap, int));
	else if ((*p)->size == 'h')
		val = (short int)(va_arg((*p)->ap, int));
	else if ((*p)->size == 'L')
		val = (long long int)(va_arg((*p)->ap, long long int));
	else if ((*p)->size == 'l')
		val = (long int)(va_arg((*p)->ap, long int));
	else
		val = (int)va_arg((*p)->ap, int);
	(*p)->int_val = (intmax_t)val;
}

void	ft_choose_value(t_printf **p)
{
	if ((*p)->type == 'u' || (*p)->type == 'o' ||
		(*p)->type == 'x' || (*p)->type == 'X' || (*p)->type == 'p')
		ft_uint_value(p);
	else if ((*p)->type == 's')
		(*p)->str_val = (char *)(va_arg((*p)->ap, char *));
	else if ((*p)->type == 'f' && ((*p)->size == 'L'))
		(*p)->double_val = (long double)(va_arg((*p)->ap, long double));
	else if ((*p)->type == 'f' || (*p)->type == 'F')
		(*p)->double_val = (double)(va_arg((*p)->ap, double));
	else if ((*p)->type == 0)
		(*p)->int_val = (intmax_t)((*p)->format[(*p)->index - 1]);
	else if ((*p)->type == 'c')
	{
		if ((*p)->size == 'l')
			(*p)->int_val = (unsigned long)(va_arg((*p)->ap, unsigned long));
		else
			(*p)->int_val = (intmax_t)(va_arg((*p)->ap, intmax_t));
	}
	else
		ft_int_value(p);
}
