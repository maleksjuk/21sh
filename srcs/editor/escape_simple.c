/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:48:38 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/24 21:57:45 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			check_escape_line(t_reader *rdr)
{
	int	i;

	if (ft_strnequ(rdr->esc, ESC_LEFT, 3) && rdr->pos > 0)
	{
		(rdr->pos)--;
		if (rdr->curs_pos[0] == 0)
		{
			ft_putstr_fd(tgetstr(TERM_UP, NULL), g_term->fd);
			i = 0;
			while (i++ < rdr->ws.ws_col)
				ft_putstr_fd(tgetstr(TERM_RIGHT, NULL), g_term->fd);
		}
		else
			ft_putstr_fd(tgetstr(TERM_LEFT, NULL), g_term->fd);
		return (1);
	}
	else if (ft_strnequ(rdr->esc, ESC_RIGHT, 3) && rdr->buff[rdr->pos] != '\0')
	{
		(rdr->pos)++;
		if (rdr->curs_pos[0] == rdr->ws.ws_col - 1)
		{
			ft_putstr_fd(tgetstr(TERM_DOWN, NULL), g_term->fd);
			ft_putstr_fd(tgetstr(TERM_CARRET, NULL), g_term->fd);
		}
		else
			ft_putstr_fd(tgetstr(TERM_RIGHT, NULL), g_term->fd);
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
	spec_symbol_home(rdr);
	ft_putstr_fd(tgetstr(TERM_CLEAR, NULL), g_term->fd);
	rdr->pos = ft_strlen(current->buff);
	rdr->len = rdr->pos;
	ft_printf("%s", current->buff);
	return (current);
}
