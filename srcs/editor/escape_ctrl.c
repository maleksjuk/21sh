/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:52:51 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/24 22:33:41 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int	check_escape_ctrl_left(t_reader *rdr)
{
	int	i;

	if (!ft_strnequ(rdr->esc, ESC_CTRL_LEFT, 6))
		return (0);
	while (rdr->buff && rdr->pos > 0)
	{
		update_cursor_position(rdr);
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
		if (rdr->pos != rdr->len && rdr->buff[rdr->pos] == ' ')
			break ;
	}
	return (1);
}

int	check_escape_ctrl_right(t_reader *rdr)
{
	if (!ft_strnequ(rdr->esc, ESC_CTRL_RIGHT, 6))
		return (0);
	while (rdr->buff && rdr->pos < rdr->len)
	{
		update_cursor_position(rdr);
		(rdr->pos)++;
		if (rdr->curs_pos[0] == rdr->ws.ws_col - 1 &&
			rdr->curs_pos[1] < rdr->height)
		{
			ft_putstr_fd(tgetstr(TERM_DOWN, NULL), g_term->fd);
			ft_putstr_fd(tgetstr(TERM_CARRET, NULL), g_term->fd);
		}
		else
			ft_putstr_fd(tgetstr(TERM_RIGHT, NULL), g_term->fd);
		if (!rdr->buff[rdr->pos] || rdr->buff[rdr->pos] == ' ')
			break ;
	}
	return (1);
}

int	check_escape_ctrl_up(t_reader *rdr)
{
	int	i;

	if (!ft_strnequ(rdr->esc, ESC_CTRL_UP, 6))
		return (0);
	if (rdr->height > 0 && rdr->curs_pos[1] > 0)
	{
		rdr->pos -= rdr->ws.ws_col;
		ft_putstr_fd(tgetstr(TERM_UP, NULL), g_term->fd);
		if (rdr->curs_pos[1] == 1 && rdr->curs_pos[0] < 7)
		{
			ft_putstr_fd(tgetstr(TERM_CARRET, NULL), g_term->fd);
			i = 7;
			while (i-- > 0)
				ft_putstr_fd(tgetstr(TERM_RIGHT, NULL), g_term->fd);
		}
	}
	else
		spec_symbol_home(rdr);
	return (1);
}

int	check_escape_ctrl_down(t_reader *rdr)
{
	int	last;

	if (!ft_strnequ(rdr->esc, ESC_CTRL_DOWN, 6))
		return (0);
	if (rdr->height > 0 && rdr->curs_pos[1] < rdr->height)
	{
		rdr->pos = rdr->pos > rdr->len ? rdr->len : rdr->pos + rdr->ws.ws_col;
		ft_putstr_fd(tgetstr(TERM_DOWN, NULL), g_term->fd);
		ft_putstr_fd(tgetstr(TERM_CARRET, NULL), g_term->fd);
		ft_printf("\033[%dC", rdr->curs_pos[0]);
		last = (rdr->len + 7) % rdr->ws.ws_col;
		if (rdr->curs_pos[1] + 1 == rdr->height && last < rdr->curs_pos[0])
		{
			ft_putstr_fd(tgetstr(TERM_CARRET, NULL), g_term->fd);
			while (last-- > 0)
				ft_putstr_fd(tgetstr(TERM_RIGHT, NULL), g_term->fd);
		}
	}
	else
		spec_symbol_end(rdr);
	return (1);
}

int	check_escape_ctrl(t_reader *rdr)
{
	if (check_escape_ctrl_left(rdr) || check_escape_ctrl_right(rdr) ||
		check_escape_ctrl_up(rdr) || check_escape_ctrl_down(rdr))
		return (1);
	return (0);
}
