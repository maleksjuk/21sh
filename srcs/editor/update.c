/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:57:13 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/15 19:42:11 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	move_cursor(struct winsize *ws, ssize_t len)
{
	int	i;

	// ft_printf("\033[0;0H");

	if (!ws->ws_col)
		return ;
	i = (len + 7) / ws->ws_col;
	if (!i)
		return ;
	// while (i - 1 > ws->ws_col)
	// i = 0;
	while (i > 0)
	{
		ft_printf("%s", ESC_UP);
		i--;
	}
	ft_printf("\r");
}

void	clear_line(int pos, ssize_t len, struct winsize *ws)
{
	ssize_t	i;

	move_cursor(ws, len - 2);

	// i = pos;
	// ft_printf("%s", ESC_LEFT);
	// while (i++ <= len)
	// 	write(1, " ", 1);
	ft_printf("\r");
	print_prompt();
	i = 0;
	while (++i <= len)
		write(1, " ", 1);

	move_cursor(ws, len - 2);
}

void    print_buffer_actual(char *buff, ssize_t len, int pos, struct winsize *ws)
{
	ssize_t	i;
	
	clear_line(pos, len + 1, ws);

	// i = pos - 2;
	// while (++i < len && buff[i])
	// 	ft_printf("%c", buff[i]);
	ft_printf("\r");
	i = 0;
	print_prompt();
	while (i < len)
		ft_printf("%c", buff[i++]);
	while (--len >= pos && len >= 0)
		ft_printf("%s", ESC_LEFT);
}

void	update_buffer(char c, char *buff, int *pos, ssize_t *len)
{
	int i;

	i = ++(*len);
	while (--i > *pos)
		buff[i] = buff[i - 1];
	buff[(*pos)++] = c;
}

void	backspace(char *buff, int *pos, ssize_t *len)
{
	int	i;

	if (*pos == 0 || *len == 0)
		return ;
	i = *pos - 1;
	while (++i <= *len)
		buff[i - 1] = buff[i];
	buff[--(*len)] = '\0';
	(*pos)--;
}
