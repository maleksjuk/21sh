/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_solver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 20:53:44 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/03 21:21:36 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		x_minus(t_printf **p, char *str, int tab[4], char *trans)
{
	if ((*p)->hash)
	{
		str[tab[2]++] = '0';
		str[tab[2]++] = (char)tab[3];
	}
	tab[2] += for_precision(p, tab[0] - (*p)->hash * 2, &str[tab[2]]);
	ft_strcpy(&str[tab[2]], trans);
	if ((*p)->hash)
		tab[2] += tab[0] - 2;
	else
		tab[2] += tab[0];
	tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
	str[tab[2]] = '\0';
}

void		x_zero(t_printf **p, char *str, int tab[4], char *trans)
{
	if ((*p)->hash)
	{
		str[tab[2]++] = '0';
		str[tab[2]++] = (char)tab[3];
	}
	tab[2] += simvol_out(p, tab[0], '0', &str[tab[2]]);
	ft_strcpy(&str[tab[2]], trans);
}

void		x_default(t_printf **p, char *str, int tab[4], char *trans)
{
	int	help;

	help = (*p)->precision + (*p)->hash * 2;
	if ((*p)->precision > tab[0])
		tab[2] += simvol_out(p, help, ' ', &str[tab[2]]);
	else if ((*p)->precision - tab[0] + (*p)->hash * 2 > 0)
	{
		help = tab[0] + (*p)->precision - tab[0] + (*p)->hash * 2;
		tab[2] += simvol_out(p, help, ' ', &str[tab[2]]);
	}
	else
		tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
	if ((*p)->hash)
	{
		str[tab[2]++] = '0';
		str[tab[2]++] = (char)tab[3];
		tab[0] -= 2;
	}
	tab[2] += for_precision(p, tab[0], &str[tab[2]]);
	ft_strcpy(&str[tab[2]], trans);
}

static int	x_continue(t_printf **p, char *str, int tab[4], char *trans)
{
	char	*tmp;

	if ((*p)->minus)
		x_minus(p, str, tab, trans);
	else if ((*p)->zero && (*p)->precision < 0)
		x_zero(p, str, tab, trans);
	else
		x_default(p, str, tab, trans);
	(*p)->final_len += ft_strlen(str);
	tmp = (*p)->final_str;
	(*p)->final_str = ft_strjoin_len((*p)->final_str, str,
			ft_strlen(str), (*p)->final_len - ft_strlen(str));
	free(trans);
	free(str);
	free(tmp);
	return (0);
}

int			ft_x_universe(t_printf **p, char c, char x)
{
	uintmax_t	num;
	char		*str;
	char		*trans;
	int			tab[4];

	tab[3] = (int)x;
	tab[2] = 0;
	num = (*p)->uint_val;
	if (num == 0)
		(*p)->hash = 0;
	if (!(trans = ft_strnew(25)))
		return (1);
	tab[0] = transform(num, 16, c, trans) + 1;
	tab[1] = max_val(tab[0], max_val((*p)->precision,
			(*p)->width)) + (*p)->hash * 2;
	if (!(str = ft_strnew(tab[1] + (*p)->hash * 2 + 4)))
		return (1);
	if ((*p)->hash)
		tab[0] += 2;
	if (num == 0 && (*p)->precision == 0)
	{
		trans[0] = '\0';
		tab[0] = 0;
	}
	return (x_continue(p, str, tab, trans));
}
