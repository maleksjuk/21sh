/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:27:51 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/21 16:28:02 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_reader	*set_reader(int fd, t_history *current)
{
	t_reader	*rdr;

	rdr = (t_reader *)malloc(sizeof(t_reader));
	rdr->oldt = (struct termios *)malloc(sizeof(struct termios));
	rdr->newt = (struct termios *)malloc(sizeof(struct termios));
	tcgetattr(STDIN_FILENO, rdr->oldt);
	*(rdr->newt) = *(rdr->oldt);
	rdr->newt->c_lflag &= ~(ICANON | ECHOCTL | ECHO | ISIG);
	rdr->newt->c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, rdr->newt);
	ioctl(1, TIOCGSIZE, &rdr->ws);
	rdr->pos = 0;
	rdr->len = 0;
	rdr->esc[0] = ESC;
	rdr->fd = fd;
	if (current)
		rdr->buff = current->buff;
	else
		rdr->buff = ft_strnew(HIST_BUFF_LEN * 4);
	return (rdr);
}

char		*unset_reader(t_reader *rdr)
{
	char	*buff;

	buff = rdr->buff;
	rdr->oldt->c_lflag &= 0x200005cb;
	tcsetattr(STDIN_FILENO, TCSANOW, rdr->oldt);
	free(rdr->oldt);
	free(rdr->newt);
	free(rdr);
	return (buff);
}
