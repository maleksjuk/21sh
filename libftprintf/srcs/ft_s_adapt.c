/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_adapt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:57:25 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/01 15:58:45 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	s_minus(t_printf **p, char *num, char *str, int tab[2])
{
	int	i;

	if ((*p)->precision > -1 && ((*p)->precision < (*p)->width ||
		(*p)->width == 0))
	{
		i = tab[0];
		tab[0] = 0;
		while (((*p)->precision - tab[1] > 0) && (num[tab[0]]))
			str[tab[1]++] = num[tab[0]++];
		tab[0] = 0;
		while ((*p)->precision - tab[0] > i && (*p)->width > 0)
		{
			str[tab[1]++] = ' ';
			i++;
		}
		tab[1] += simvol_out(p, tab[1], ' ', &str[tab[1]]);
	}
	else
	{
		ft_strcpy(str, num);
		tab[1] += tab[0];
		tab[1] += simvol_out(p, tab[0], ' ', &str[tab[1]]);
	}
}

void	s_zero(t_printf **p, char *num, char *str, int tab[2])
{
	if ((*p)->precision > -1 && ((*p)->precision < (*p)->width ||
		(*p)->width == 0))
	{
		while ((*p)->width - (*p)->precision > tab[1])
			str[tab[1]++] = '0';
		tab[0] = 0;
		while ((*p)->precision - tab[0] > 0)
			str[tab[1]++] = num[tab[0]++];
	}
	else
	{
		if ((*p)->width > tab[0])
			while (tab[1] < (*p)->width - tab[0])
				str[tab[1]++] = '0';
		else
			while ((*p)->width + tab[1] < tab[0] - 1)
				str[tab[1]++] = '0';
		ft_strcpy(&str[tab[1]], num);
	}
}

void	s_default(t_printf **p, char *num, char *str, int tab[2])
{
	int	i;

	if ((*p)->precision > -1 && ((*p)->precision <= (*p)->width ||
		(*p)->width == 0))
	{
		while ((*p)->width - (*p)->precision > tab[1])
			str[tab[1]++] = ' ';
		i = 0;
		while ((*p)->precision - i > tab[0] && (*p)->width > 0)
		{
			str[tab[1]++] = ' ';
			i++;
		}
		tab[0] = 0;
		while ((*p)->precision - tab[0] > 0)
			str[tab[1]++] = num[tab[0]++];
	}
	else
	{
		tab[1] += simvol_out(p, tab[0], ' ', str);
		ft_strncpy(&str[tab[1]], num,
				(*p)->precision == -1 ? ft_strlen(num) : (*p)->precision);
	}
}
