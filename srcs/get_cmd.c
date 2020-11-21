/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:43:15 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/21 16:36:28 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "editor.h"

t_history	*check_escape_main(t_reader *rdr, t_history *current)
{
	int	i;

	i = 1;
	rdr->height = (ft_strlen(rdr->buff) + 7) / rdr->ws.ws_col;
	rdr->curs_pos[0] = (rdr->pos + 7) % rdr->ws.ws_col;
	rdr->curs_pos[1] = (rdr->pos + 7) / rdr->ws.ws_col;
	while (!ft_isalpha(rdr->esc[i - 1]))
		read(rdr->fd, &rdr->esc[i++], 1);
	rdr->esc[i] = '\0';
	if (ft_strnequ(rdr->esc, ESC_HOME, 3))
		rdr->c = CTRL_A;
	else if (ft_strnequ(rdr->esc, ESC_END, 3))
		rdr->c = CTRL_E;
	else if (!check_escape_ctrl(rdr))
		if (!check_escape_line(rdr))
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
	{
		ft_strcpy(rdr->esc, rdr->c == CTRL_A ? ESC_CTRL_UP : ESC_CTRL_DOWN);
		i = rdr->len / rdr->ws.ws_col + 1;
		while (i--)
			check_escape_ctrl(rdr);
	}
	else if (rdr->c == DEL)
	{
		backspace(rdr);
		print_buffer_actual(rdr);
		i = 0;
	}
	else
		i = 0;
	return (i);
}

char		*get_cmd(int fd)
{
	t_history	*current;
	t_reader	*rdr;

	if (!g_hist)
		g_hist = new_history(NULL, NULL);
	current = g_hist;
	rdr = set_reader(fd, current);
	while (read(rdr->fd, &rdr->c, 1) > 0)
	{
		if (rdr->c == '\n')
		{
			if (ft_strlen(rdr->buff) != 0)
			{
				g_hist = new_history(current, g_hist);
				rdr->buff = g_hist->prev->buff;
				reset_history(current);
			}
			break ;
		}
		else if (rdr->c == ESC)
			current = check_escape_main(rdr, current);
		else if (ft_isprint(rdr->c))
		{
			update_buffer(rdr);
			print_buffer_actual(rdr);
		}
		if (spec_symbol(rdr, current, 1) > 0)
			break ;
		check_length_buffer(current);
		rdr->buff = current->buff;
	}
	/*
	** if (DEBUG)
	** {
	** 	while (current->prev)
	** 		current = current->prev;
	** 	while (current->next)
	** 	{
	** 		ft_printf("\n%sHIST: |[%p] - b[%s] - s[%s]|%s", CLR_YELLOW, current->buff, current->buff, current->save, CLR_RESET);
	** 		current = current->next;
	** 	}
	** }
	*/
	ft_printf("\n");
	return (unset_reader(rdr));
}
