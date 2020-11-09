/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:57:13 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/09 21:58:31 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	clear_line(int pos, int len)
{
	int	i;

	i = pos;
	write(1, KEY_LEFT_, 3);
	while (i++ <= len)
		write(1, " ", 1);
	write(1, "\r", 1);
	i = 0;
	while (++i < pos)
		write(1, " ", 1);
}

void    print_buffer_actual(char *buff, int len, int pos)
{
	int	i;

	clear_line(pos, len + 1);
	i = pos - 2;
	while (++i < len)
		if (buff[i])
			write(1, &buff[i], 1);
	write(1, "\r", 1);
	i = -1;
	while (++i < pos)
		write(1, &buff[i], 1);
}

void	reset_history(t_history *hist)
{
	int i;

	while (hist)
	{
		free(hist->buff);
		hist->buff = new_str(BUFF_LEN * hist->count);
		strcpy(hist->buff, hist->save);
		hist = hist->prev;
	}
}

void	update_buffer(char c, char *buff, int *pos, int *len)
{
	int i;

	i = *len + 1;
	while (--i > *pos)
		buff[i] = buff[i - 1];
	buff[(*pos)++] = c;
	(*len)++;
}
