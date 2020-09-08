/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_o.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:31:17 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/03 21:11:23 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		o_minus(t_printf **p, char *str, int tab[3], char *trans)
{
	if ((*p)->hash)
		str[tab[2]++] = '0';
	tab[2] += for_precision(p, tab[0] - (*p)->hash, &str[tab[2]]);
	ft_strncpy(&str[tab[2]], trans, tab[0]);
	if ((*p)->hash)
		tab[2] += tab[0] - 1;
	else
		tab[2] += tab[0];
	tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
}

void		o_zero(t_printf **p, char *str, int tab[3], char *trans)
{
	if ((*p)->hash)
		str[tab[2]++] = '0';
	tab[2] += for_precision(p, tab[0], &str[tab[2]]);
	tab[2] += simvol_out(p, tab[0], '0', &str[tab[2]]);
	ft_strncpy(&str[tab[2]], trans, tab[0]);
}

void		o_default(t_printf **p, char *str, int tab[3], char *trans)
{
	int	help;

	help = tab[0] + (*p)->precision - tab[0];
	if ((*p)->precision > tab[0])
		tab[2] += simvol_out(p, help, ' ', &str[tab[2]]);
	else
		tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
	if ((*p)->hash)
	{
		str[tab[2]++] = '0';
		tab[0]--;
	}
	tab[2] += for_precision(p, tab[0], &str[tab[2]]);
	ft_strncpy(&str[tab[2]], trans, tab[0]);
}

static int	o_continue(t_printf **p, char *str, int tab[3], char *trans)
{
	char	*tmp;

	if ((*p)->hash)
		tab[0]++;
	if ((*p)->minus)
		o_minus(p, str, tab, trans);
	else if ((*p)->zero && (*p)->precision < 0)
		o_zero(p, str, tab, trans);
	else
		o_default(p, str, tab, trans);
	(*p)->final_len += ft_strlen(str);
	tmp = (*p)->final_str;
	(*p)->final_str = ft_strjoin_len((*p)->final_str, str,
			ft_strlen(str), (*p)->final_len - ft_strlen(str));
	free(trans);
	free(str);
	free(tmp);
	return (0);
}

int			ft_o(t_printf **p)
{
	uintmax_t	num;
	char		*str;
	char		*trans;
	int			tab[3];

	tab[2] = 0;
	num = (*p)->uint_val;
	trans = ft_strnew(25);
	if (!trans)
		return (1);
	tab[0] = transform(num, 8, '0', trans) + 1;
	trans[tab[0]] = '\0';
	tab[1] = max_val(tab[0], max_val((*p)->precision,
			(*p)->width)) + (*p)->hash;
	if (!(str = ft_strnew(tab[1] + 3)))
		return (1);
	if (((*p)->precision > tab[0] && num != 0) || (num == 0 &&
		(*p)->precision > 0))
		(*p)->hash = 0;
	if (num == 0 && ((*p)->precision == 0 || (*p)->hash))
	{
		trans[0] = '\0';
		tab[0] = 0;
	}
	return (o_continue(p, str, tab, trans));
}
