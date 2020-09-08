/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:39:52 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/02 15:36:57 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*num_null(void)
{
	char	*num;

	num = ft_strnew(7);
	ft_strcpy(num, "(null)\0");
	return (num);
}

void		s_return(t_printf **p, char *str)
{
	char	*tmp;

	(*p)->final_len += ft_strlen(str);
	tmp = (*p)->final_str;
	(*p)->final_str = ft_strjoin_len((*p)->final_str, str,
			ft_strlen(str), (*p)->final_len - ft_strlen(str));
	free(str);
	free(tmp);
}

int			ft_s(t_printf **p)
{
	char	*num;
	char	*str;
	int		tab[2];

	if ((*p)->str_val)
		num = ft_strdup((*p)->str_val);
	else
		num = num_null();
	tab[0] = ft_strlen(num);
	tab[1] = max_val(tab[0], max_val((*p)->precision, (*p)->width));
	str = ft_strnew(tab[1] + 1);
	if (!str)
		return (1);
	if (ft_strequ(num, "") || (*p)->double_val)
		(*p)->precision = -1;
	tab[1] = 0;
	if ((*p)->minus)
		s_minus(p, num, str, tab);
	else if ((*p)->zero && !((*p)->double_val))
		s_zero(p, num, str, tab);
	else
		s_default(p, num, str, tab);
	free(num);
	s_return(p, str);
	return (0);
}
