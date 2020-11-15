/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:52:45 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/11/15 19:59:08 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "editor.h"

static int	iseof_in_line(char *line)
{
	while (*line)
	{
		if (*line == 4)
			return (1);
		++line;
	}
	return (0);
}

static char	*tweak(int i, char *bufer, int buf_size)
{
	char *overflow;

	overflow = ft_strnew(buf_size);
	ft_strncpy(overflow, bufer, i);
	free(bufer);
	return (overflow);
}

static char	*get_cm(int fd, int i, int n, int buf_size)
{
	char	*bufer;
	char	smbl[1];
	char	*overflow;

	bufer = ft_strnew(buf_size);
	while (n > 0)
	{
		n = read(fd, smbl, 1);
		if (n == 0)
		{
			bufer[0] = 4;
			bufer[1] = 0;
			break ;
		}
		if (*smbl == '\n')
			break ;
		bufer[i++] = smbl[0];
		if (i == buf_size)
		{
			buf_size *= 2;
			overflow = tweak(i, bufer, buf_size);
			bufer = overflow;
		}
	}
	return (bufer);
}








char	*get_cmd_2(int fd)
{
	static struct termios oldt;

	init_term(&oldt);

	char c;
	char esc[3];
	char *buff;
	int pos;
	int len;

	struct winsize ws;
	struct winsize ws_curr;
	ioctl(1, TIOCGSIZE, &ws);

	ws_curr.ws_col = 0;
	ws_curr.ws_row = 0;

	t_history	*current;

	if (!g_hist)
		g_hist = new_history(NULL, NULL);
	current = g_hist;
	buff = current->buff;

	pos = 0;
	len = 0;
	esc[0] = ESC;

	while (read(fd, &c, 1) > 0)
	{
		if (c == 4 && ft_strlen(buff) == 0)
		{
			buff = "\x04";
			break ;
		}
		else if (c == 3)
		{
			reset_history(current);
			ft_strclr(g_hist->buff);
			buff = g_hist->buff;
			break ;
		}
		else if (c == '\n')
		{
			if (ft_strlen(buff) != 0)
			{
				// g_hist = new_history(current, g_hist);
				buff = g_hist->prev->buff;
				reset_history(current);
			}
			break ;
		}
		else if (c == DEL)
		{
			backspace(buff, &pos, &len);
			print_buffer_actual(buff, len, pos, &ws);
		}
		else if (c == ESC)
		{
			read(1, &esc[1], 2);
			// check_escape_ctrl(esc);
			if (!check_escape_line(esc, buff, &pos))
				current = check_escape_history(esc, buff, &pos, current);
			buff = current->buff;

		}
		else if (ft_isprint(c))
		{
			update_buffer(c, buff, &pos, &len);
			print_buffer_actual(buff, len, pos, &ws);
		}
		check_length_buffer(current);
		if ((ft_strlen(buff) + 7) % ws.ws_col == 0)
			ft_printf("\n");
		buff = current->buff;
		if (DEBUG)
			if (c == '\t')
				exit(1);
	}

	ft_printf("\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (ft_strdup(buff));
}








char		*get_txt(char *word, int i)
{
	char	*bufer;
	char	*res;
	char	*help;

	res = ft_strnew(1);
	help = ft_strnew(1);
	while (1)
	{
		ft_printf("\033[31mheredoc> \033[0m");
		bufer = get_cmd_2(0);
		// bufer = get_cm(0, 0, 1, 1024);
		if (ft_strequ(bufer, word) || iseof_in_line(bufer))
		{
			free(bufer);
			break ;
		}
		if (i == 0)
			help = ft_strjoin(res, "\n");
		else
			i = 0;
		free(res);
		res = ft_strjoin(help, bufer);
		free(help);
		free(bufer);
	}
	return (res);
}
