/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_adapt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:14:05 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/01 21:21:44 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	d_minus(t_printf **p, char *str, int tab[5], char *num_str)
{
	if (tab[4])
		str[tab[2]++] = '-';
	else if ((*p)->plus && !tab[4])
		str[tab[2]++] = '+';
	else if ((*p)->space && !tab[4])
		str[tab[2]++] = ' ';
	tab[2] += for_precision(p, tab[0] - tab[3], &str[tab[2]]);
	ft_strcpy(&str[tab[2]], num_str);
	if (tab[3])
		tab[2]--;
	tab[2] += tab[0];
	tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
}

void	d_zero(t_printf **p, char *str, int tab[5], char *num_str)
{
	if (tab[4])
		str[tab[2]++] = '-';
	else if ((*p)->plus && !tab[4])
		str[tab[2]++] = '+';
	else if ((*p)->space)
		str[tab[2]++] = ' ';
	tab[2] += for_precision(p, tab[0] - tab[3], &str[tab[2]]);
	tab[2] += simvol_out(p, tab[0], '0', &str[tab[2]]);
	ft_strcpy(&str[tab[2]], num_str);
}

void	d_def(t_printf **p, char *str, int tab[5], char *num_str)
{
	int	help;

	help = tab[0] + (*p)->precision - tab[0] + tab[3] + 1;
	if ((*p)->precision > 0 && tab[0] < (*p)->precision)
		tab[2] += simvol_out(p, help - 1, ' ', &str[tab[2]]);
	else if (tab[4] && (*p)->precision == tab[0])
		tab[2] += simvol_out(p, tab[0] + tab[4], ' ', &str[tab[2]]);
	else if ((*p)->precision > tab[0] - tab[3])
		tab[2] += simvol_out(p, (*p)->precision + tab[3], ' ', &str[tab[2]]);
	else
		tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
	if (tab[4])
		str[tab[2]++] = '-';
	else if ((*p)->plus && !tab[4])
		str[tab[2]++] = '+';
	else if ((*p)->space && !tab[4])
		str[tab[2]++] = ' ';
	if (num_str[0] == '0' && (*p)->precision == 0)
		tab[2] += for_precision(p, tab[0] - tab[3] + 1, &str[tab[2]]);
	else
		tab[2] += for_precision(p, tab[0] - tab[3] - 1 + 1, &str[tab[2]]);
	ft_strcpy(&str[tab[2]], num_str);
}
