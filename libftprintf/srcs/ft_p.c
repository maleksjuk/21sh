/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:57:39 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/02 15:36:24 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	p_minus(t_printf **p, char *str, int tab[3], char *trans)
{
	str[tab[2]++] = '0';
	str[tab[2]++] = 'x';
	tab[2] += for_precision(p, tab[0] - 2, &str[tab[2]]);
	ft_strcpy(&str[tab[2]], trans);
	tab[2] += tab[0] - 2;
	tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
}

void	p_zero(t_printf **p, char *str, int tab[3], char *trans)
{
	str[tab[2]++] = '0';
	str[tab[2]++] = 'x';
	tab[2] += simvol_out(p, tab[0], '0', &str[tab[2]]);
	ft_strcpy(&str[tab[2]], trans);
}

void	p_default(t_printf **p, char *str, int tab[3], char *trans)
{
	int	help;

	help = (*p)->precision + 2;
	if ((*p)->precision > tab[0])
		tab[2] += simvol_out(p, help, ' ', &str[tab[2]]);
	else
		tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
	str[tab[2]++] = '0';
	str[tab[2]++] = 'x';
	tab[0] -= 2;
	tab[2] += for_precision(p, tab[0], &str[tab[2]]);
	ft_strncpy(&str[tab[2]], trans,
			(*p)->precision == -1 ? ft_strlen(trans) : (*p)->precision);
}

void	p_final(t_printf **p, char *str, char *trans)
{
	char	*tmp;

	tmp = (*p)->final_str;
	(*p)->final_len += ft_strlen(str);
	(*p)->final_str = ft_strjoin_len((*p)->final_str, str,
			ft_strlen(str), (*p)->final_len - ft_strlen(str));
	free(str);
	free(trans);
	free(tmp);
}

int		ft_p(t_printf **p)
{
	uintmax_t	num;
	char		*str;
	char		*trans;
	int			tab[3];

	tab[2] = 0;
	num = (*p)->uint_val;
	trans = ft_strnew(len_nbr(num) * 2);
	if (!trans)
		return (1);
	tab[0] = transform(num, 16, 'a', trans) + 1;
	tab[1] = max_val(tab[0], max_val((*p)->precision, (*p)->width)) + 2;
	str = ft_strnew(tab[1] + 2);
	if (!str)
		return (1);
	tab[0] += 2;
	if ((*p)->minus)
		p_minus(p, str, tab, trans);
	else if ((*p)->zero && (*p)->precision < 0)
		p_zero(p, str, tab, trans);
	else
		p_default(p, str, tab, trans);
	p_final(p, str, trans);
	return (0);
}
