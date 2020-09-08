/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:04:09 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/01 21:32:03 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_final(t_printf **p)
{
	int len;

	len = (*p)->final_len;
	write(1, (*p)->final_str, (*p)->final_len);
	free((*p)->final_str);
	free(*p);
	return (len);
}

int	ft_construct(t_printf **p)
{
	(*p)->minus = 0;
	(*p)->plus = 0;
	(*p)->zero = 0;
	(*p)->hash = 0;
	(*p)->space = 0;
	(*p)->width = 0;
	(*p)->precision = -1;
	(*p)->uppercase = 0;
	(*p)->int_val = 0;
	(*p)->uint_val = 0;
	(*p)->double_val = 0;
	(*p)->type = 0;
	(*p)->size = 0;
	(*p)->spec_mask = "diouxXcsfp";
	(*p)->size_mask = "hlL";
	(*p)->str_val = NULL;
	return (0);
}

int	ft_printf(const char *format, ...)
{
	t_printf *p;

	if (!(p = (t_printf*)malloc(sizeof(t_printf))))
		return (-1);
	if (format[0] == '\0')
		return (0);
	va_start(p->ap, format);
	p->final_len = 0;
	p->index = 0;
	p->final_str = NULL;
	p->format = (char *)format;
	while (format[p->index] != '\0')
	{
		ft_construct(&p);
		if (ft_pars(&p) == -1)
			break ;
	}
	va_end(p->ap);
	return (ft_final(&p));
}
