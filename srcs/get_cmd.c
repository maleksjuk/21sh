/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:43:15 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/25 21:35:57 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "editor.h"

void		update_cursor_position(t_reader *rdr)
{
	rdr->height = (ft_strlen(rdr->buff) + rdr->prompt_len) / rdr->ws.ws_col;
	rdr->curs_pos[0] = (rdr->pos + rdr->prompt_len) % rdr->ws.ws_col;
	rdr->curs_pos[1] = (rdr->pos + rdr->prompt_len) / rdr->ws.ws_col;
}

t_history	*check_escape_main(t_reader *rdr, t_history *current)
{
	int	i;

	i = 1;
	update_cursor_position(rdr);
	while (rdr->c != '\xe2' && !ft_isalpha(rdr->esc[i - 1]) &&
		rdr->esc[i - 1] != '~')
		read(rdr->fd, &rdr->esc[i++], 1);
	rdr->esc[i] = '\0';
	if (ft_strnequ(rdr->esc, ESC_HOME, 3))
		rdr->c = CTRL_A;
	else if (ft_strnequ(rdr->esc, ESC_END, 3))
		rdr->c = CTRL_E;
	else if (cut_copy_paste(rdr, current))
		(void)NULL;
	else if (!check_escape_ctrl(rdr))
		if (!check_escape_line(rdr, 0))
			current = check_escape_history(rdr, current);
	rdr->buff = current->buff;
	return (current);
}

int			spec_symbol(t_reader *rdr, t_history *current, int i)
{
	if (rdr->c == CTRL_D && ft_strlen(rdr->buff) == 0)
		rdr->buff = "\x04";
	else if (rdr->c == CTRL_C)
	{
		reset_history(current);
		ft_strclr(g_hist->buff);
		rdr->buff = g_hist->buff;
	}
	else if (rdr->c == CTRL_A || rdr->c == CTRL_E)
		i = rdr->c == CTRL_A ? spec_symbol_home(rdr) : spec_symbol_end(rdr);
	else if (rdr->c == DEL)
	{
		backspace(rdr);
		i = 0;
	}
	else
		i = 0;
	return (i);
}

int			check_enter(t_reader *rdr, t_history *current)
{
	if (rdr->c != '\n')
		return (0);
	if (ft_strlen(rdr->buff) != 0)
	{
		if (!ft_isspace_str(rdr->buff))
		{
			g_hist = new_history(current, g_hist);
			rdr->buff = g_hist->prev->buff;
		}
		else
			rdr->buff = "";
	}
	update_cursor_position(rdr);
	while (rdr->curs_pos[1]++ < rdr->height)
	{
		ft_putstr_fd(tgetstr(TERM_DOWN, NULL), g_term->fd);
		rdr->pos += rdr->ws.ws_col;
	}
	while (rdr->pos++ < rdr->len)
		ft_putstr_fd(tgetstr(TERM_RIGHT, NULL), g_term->fd);
	reset_history(current);
	return (1);
}

char		*get_cmd(int fd)
{
	t_history	*current;
	t_reader	*rdr;

	if (!g_hist)
		g_hist = new_history(NULL, NULL);
	current = g_hist;
	rdr = set_reader(fd, current);
	rdr->prompt_len = 7;
	while (read(rdr->fd, &rdr->c, 1) > 0)
	{
		if (check_enter(rdr, current))
			break ;
		else if (rdr->c == ESC || rdr->c == '\xe2')
			current = check_escape_main(rdr, current);
		else if (ft_isprint(rdr->c))
		{
			update_buffer(rdr);
			print_buffer_actual(rdr);
		}
		if (spec_symbol(rdr, current, 1) > 0)
			break ;
		check_length_buffer(current, rdr->len);
		rdr->buff = current->buff;
	}
	ft_printf("\n");
	return (unset_reader(rdr));
}
