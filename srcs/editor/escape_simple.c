/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:48:38 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/21 16:18:16 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			check_escape_line(t_reader *rdr)
{
	if (ft_strnequ(rdr->esc, ESC_LEFT, 3) && rdr->pos > 0)
	{
		(rdr->pos)--;
		ft_printf("%s", ESC_LEFT);
		return (1);
	}
	else if (ft_strnequ(rdr->esc, ESC_RIGHT, 3) && rdr->buff[rdr->pos] != '\0')
	{
		(rdr->pos)++;
		if (rdr->curs_pos[0] == rdr->ws.ws_col - 1)
			ft_printf("%s\r", ESC_DOWN);
		else
			ft_printf("%s", ESC_RIGHT);
		return (1);
	}
	return (0);
}

t_history	*check_escape_history(t_reader *rdr, t_history *current)
{
	if (current && ft_strnequ(rdr->esc, ESC_UP, 3) && current->prev)
		current = current->prev;
	else if (current && ft_strnequ(rdr->esc, ESC_DOWN, 3) && current->next)
		current = current->next;
	else
		return (current);
	ft_printf("\r");
	print_prompt();
	rdr->pos = -1;
	while (rdr->buff[++(rdr->pos)])
		write(1, " ", 1);
	ft_printf("\r");
	print_prompt();
	rdr->pos = ft_strlen(current->buff);
	ft_printf("%s", current->buff);
	return (current);
}
