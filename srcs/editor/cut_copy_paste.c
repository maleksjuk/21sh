/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 06:17:35 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/22 06:31:06 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			cut_copy_paste(t_reader *rdr)
{
	if (ft_strnequ(rdr->esc, OPT_C, 4))
		ft_printf("opt_c\n");
	else if (ft_strnequ(rdr->esc, OPT_V, 6))
		ft_printf("opt_v\n");
	else if (ft_strnequ(rdr->esc, OPT_X, 6))
		ft_printf("opt_x\n");
	else
		return (0);
	return (1);
}
