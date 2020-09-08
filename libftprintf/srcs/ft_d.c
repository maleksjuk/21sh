/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:30:22 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/01 16:14:26 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char		*ft_num_str(t_printf **p, intmax_t num, int tab[5])
{
	char	*num_str;

	if (num / 10 == MAX_INT && num % 10 == -8)
	{
		num_str = ft_strnew(22);
		if (!num_str)
			return (NULL);
		ft_strcpy(num_str, "9223372036854775808\0");
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
		tab[0]--;
	}
	return (num_str);
}

static int	d_continue(t_printf **p, char *str, int tab[5], char *num_str)
{
	char *tmp;

	if ((*p)->minus)
		d_minus(p, str, tab, num_str);
	else if ((*p)->zero && (*p)->precision < 0)
		d_zero(p, str, tab, num_str);
	else
		d_def(p, str, tab, num_str);
	(*p)->final_len += ft_strlen(str);
	tmp = (*p)->final_str;
	(*p)->final_str = ft_strjoin_len((*p)->final_str, str,
			ft_strlen(str), (*p)->final_len - ft_strlen(str));
	free(tmp);
	free(str);
	free(num_str);
	return (0);
}

int			ft_d(t_printf **p)
{
	intmax_t	num;
	char		*str;
	char		*num_str;
	int			tab[5];

	tab[2] = 0;
	tab[3] = 0;
	tab[4] = 0;
	num = (*p)->int_val;
	if (num < 0 || (*p)->plus || (*p)->space)
		tab[3] = 1;
	tab[0] = len_nbr(num);
	if (tab[3])
		tab[0]++;
	tab[1] = max_val(tab[0], max_val((*p)->precision, (*p)->width)) + tab[3];
	str = ft_strnew(tab[1] + 1);
	if (!str)
		return (1);
	num_str = ft_num_str(p, num, tab);
	if (num < 0)
	{
		num *= -1;
		tab[4] = 1;
	}
	return (d_continue(p, str, tab, num_str));
}
