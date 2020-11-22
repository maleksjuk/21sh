/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:57:13 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/22 03:47:35 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	move_cursor(struct winsize ws, int pos)
{
	int	i;

	if (!ws.ws_col)
		return ;
	i = (pos + 7) / ws.ws_col;
	if (!i)
		return ;
	while (i-- > 0)
		ft_printf("%s", ESC_UP);
	ft_printf("\r");
}

void	clear_line(t_reader *rdr)
{
	ssize_t	i;

	move_cursor(rdr->ws, rdr->len - 2);
	ft_printf("\r");
	print_prompt();
	i = 0;
	while (++i < rdr->len)
		write(1, " ", 1);
	move_cursor(rdr->ws, rdr->len - 2);
}

void	print_buffer_actual(t_reader *rdr)
{
	ssize_t	i;

	// clear_line(rdr);
	// ft_printf("\r");
	ft_putstr_fd(tgetstr(TERM_CLEAR, NULL), g_term->fd);
	i = rdr->pos - 1;
	// print_prompt();
	while (i < rdr->len)
		ft_printf("%c", rdr->buff[i++]);
	if ((rdr->pos + 7) % rdr->ws.ws_col == 0)
		ft_putstr_fd(tgetstr(TERM_DOWN, NULL), g_term->fd);
	i = rdr->len;
	while (--i >= rdr->pos && i >= 0)
		ft_printf("%s", ESC_LEFT);
}

void	update_buffer(t_reader *rdr)
{
	int i;

	i = ++(rdr->len);
	while (--i > rdr->pos)
		rdr->buff[i] = rdr->buff[i - 1];
	rdr->buff[(rdr->pos)++] = rdr->c;
}

int		backspace(t_reader *rdr)
{
	int	i;

	if (rdr->pos == 0 || rdr->len == 0)
		return (0);
	i = rdr->pos - 1;
	while (++i <= rdr->len)
		rdr->buff[i - 1] = rdr->buff[i];
	rdr->buff[--(rdr->len)] = '\0';
	(rdr->pos)--;
	return (1);
}
