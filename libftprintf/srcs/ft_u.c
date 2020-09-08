/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:30:57 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/02 15:55:43 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	u_minus(t_printf **p, char *str, int tab[3], char *num_str)
{
	tab[2] += for_precision(p, tab[0], &str[tab[2]]);
	ft_strcpy(&str[tab[2]], num_str);
	tab[2] += tab[0];
	tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
	str[tab[2]] = '\0';
}

void	u_zero(t_printf **p, char *str, int tab[3], char *num_str)
{
	tab[2] += for_precision(p, tab[0], &str[tab[2]]);
	tab[2] += simvol_out(p, tab[0], '0', &str[tab[2]]);
	ft_strcpy(&str[tab[2]], num_str);
}

void	u_default(t_printf **p, char *str, int tab[3], char *num_str)
{
	if ((*p)->precision > 0 && (*p)->precision > tab[0])
		tab[2] += simvol_out(p, (*p)->precision, ' ', &str[tab[2]]);
	else
		tab[2] += simvol_out(p, tab[0], ' ', &str[tab[2]]);
	tab[2] += for_precision(p, tab[0], &str[tab[2]]);
	ft_strcpy(&str[tab[2]], num_str);
}

char	*ft_u_num_str(t_printf **p, uintmax_t num, int tab[3])
{
	char	*num_str;

	if (num / 10 == MAX_INT && num % 10 == -8)
	{
		num_str = ft_strnew(22);
		ft_strcpy(num_str, "-9223372036854775808\0");
	}
	else if (num > 10000000000)
	{
		num_str = ft_itoa(num / 10000);
		num_str = ft_strjoin(num_str, ft_itoa(num % 10000));
	}
	else
		num_str = ft_itoa(num);
	if (num_str[0] == '-')
	{
		num_str[0] = '\0';
		num_str = &num_str[1];
	}
	if (num == 0 && (*p)->precision == 0)
	{
		num_str[0] = '\0';
		tab[0] = 0;
	}
	return (num_str);
}

int		ft_u(t_printf **p)
{
	uintmax_t	num;
	char		*str;
	char		*num_str;
	int			tab[3];

	tab[2] = 0;
	num = (*p)->uint_val;
	tab[0] = len_nbr_u(num);
	tab[1] = max_val(tab[0], max_val((*p)->precision, (*p)->width));
	if (!(str = ft_strnew(tab[1] + 1)))
		return (1);
	num_str = ft_u_num_str(p, num, tab);
	if ((*p)->minus)
		u_minus(p, str, tab, num_str);
	else if ((*p)->zero && (*p)->precision < 0)
		u_zero(p, str, tab, num_str);
	else
		u_default(p, str, tab, num_str);
	(*p)->final_len += ft_strlen(str);
	free(num_str);
	num_str = (*p)->final_str;
	(*p)->final_str = ft_strjoin_len((*p)->final_str, str,
			ft_strlen(str), (*p)->final_len - ft_strlen(str));
	ft_free(str, num_str);
	return (0);
}
