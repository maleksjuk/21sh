/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:05:17 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/01 20:56:31 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_search_type(t_printf **p, int i)
{
	if ((*p)->format[i] == '\0')
		return (-1);
	if ((*p)->format[i] != '\0' &&
		ft_strchr((*p)->spec_mask, (*p)->format[i]))
		(*p)->type = (*p)->format[i];
	else if (ft_strchr("DIOUCSF", (*p)->format[i]))
	{
		(*p)->type = (*p)->format[i] + 32;
		(*p)->uppercase = 1;
	}
	if ((*p)->precision < -1 && (*p)->type == 'f')
		(*p)->precision = 6;
	else if ((*p)->precision < -1)
		(*p)->precision = -1;
	return (++i);
}

int		ft_search_spec_2(t_printf **p, int i)
{
	char *tmp1;
	char *tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	if (!(*p)->final_str)
	{
		if (!((*p)->final_str = (char *)malloc(sizeof((*p)->final_str) *
			(i + 1))))
			return (-1);
		(*p)->final_str[i] = '\0';
		(*p)->final_str = ft_strncpy((*p)->final_str, (*p)->format, i);
	}
	else
	{
		if (!(tmp1 = (char *)malloc(sizeof(tmp1) * (i + 1))))
			return (-1);
		tmp1[i] = '\0';
		tmp1 = ft_strncpy(tmp1, (*p)->format, i);
		tmp2 = (*p)->final_str;
		(*p)->final_str = ft_strjoin_len((*p)->final_str, tmp1, i,
			(*p)->final_len - i);
		ft_free(tmp1, tmp2);
	}
	return (0);
}

int		ft_search_spec_1(t_printf **p, int i)
{
	if ((*p)->final_str)
	{
		(*p)->format = (*p)->format + (*p)->index;
		i = (i == -1) ? 1 : 0;
	}
	while (((*p)->format[i]) != '\0' && ((*p)->format[i]) != '%')
		i++;
	(*p)->final_len += i;
	if (ft_search_spec_2(p, i) == -1)
		return (-1);
	if ((*p)->format[i] == '\0')
		return (-1);
	i++;
	i = ft_set_color(&((*p)->format), i);
	if ((*p)->format[i] == '%' || i == 0)
	{
		(*p)->index = i;
		if (i == 0)
			i = ft_search_spec_1(p, 0);
		else
			i = ft_search_spec_1(p, -1);
	}
	return (i);
}

void	init_type(int (*ft_type[10])(t_printf**))
{
	ft_type[0] = ft_d;
	ft_type[1] = ft_i;
	ft_type[2] = ft_o;
	ft_type[3] = ft_u;
	ft_type[4] = ft_x;
	ft_type[5] = ft_x2;
	ft_type[6] = ft_c;
	ft_type[7] = ft_s;
	ft_type[8] = ft_f;
	ft_type[9] = ft_p;
}

int		ft_choose_type(t_printf **p)
{
	int i;
	int	(*ft_type[10])(t_printf**);

	i = -1;
	init_type(ft_type);
	if ((*p)->type == 0)
	{
		ft_type[6](p);
		return (0);
	}
	while ((*p)->spec_mask[++i])
		if ((*p)->spec_mask[i] == (*p)->type)
			break ;
	if (i < 10)
		ft_type[i](p);
	return (0);
}
