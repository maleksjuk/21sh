/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 23:42:15 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/23 23:43:28 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int	spec_symbol_home(t_reader *rdr)
{
	int	i;

	update_cursor_position(rdr);
	while (rdr->curs_pos[1]-- > 0)
		ft_putstr_fd(tgetstr(TERM_UP, NULL), g_term->fd);
	ft_putstr_fd(tgetstr(TERM_CARRET, NULL), g_term->fd);
	i = 7;
	while (i--)
		ft_putstr_fd(tgetstr(TERM_RIGHT, NULL), g_term->fd);
	rdr->pos = 0;
	return (0);
}

int	spec_symbol_end(t_reader *rdr)
{
	int	i;

	update_cursor_position(rdr);
	while (rdr->curs_pos[1]++ < rdr->height)
		ft_putstr_fd(tgetstr(TERM_DOWN, NULL), g_term->fd);
	ft_putstr_fd(tgetstr(TERM_CARRET, NULL), g_term->fd);
	i = (rdr->len + 7) % rdr->ws.ws_col;
	while (i-- > 0)
		ft_putstr_fd(tgetstr(TERM_RIGHT, NULL), g_term->fd);
	rdr->pos = rdr->len;
	return (0);
}