/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:09:55 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/02 15:35:02 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <wchar.h>

int			ft_c(t_printf **p)
{
	char	c;
	char	*str;
	int		i;
	char	*tmp;

	c = (wchar_t)(*p)->int_val;
	i = max_val(1, max_val((*p)->precision, (*p)->width));
	str = ft_strnew(i + 1);
	if (!str)
		return (1);
	i = 0;
	if ((*p)->width > 1 && !(*p)->minus && !(*p)->zero)
		i = i + simvol_out(p, 1, ' ', &str[i]);
	else if ((*p)->zero && !(*p)->minus)
		i += simvol_out(p, 1, '0', &str[i]);
	str[i++] = c;
	if ((*p)->minus)
		i = i + simvol_out(p, 1, ' ', &str[i]);
	(*p)->final_len += i;
	tmp = (*p)->final_str;
	(*p)->final_str = ft_strjoin_len((*p)->final_str, str, i,
		(*p)->final_len - i);
	free(str);
	free(tmp);
	return (0);
}
