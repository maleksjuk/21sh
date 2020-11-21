/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:52:45 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/11/21 13:43:42 by obanshee         ###   ########.fr       */
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

void	clear_line_2(int pos, ssize_t len, struct winsize *ws)
{
	ssize_t	i;

	move_cursor(ws, len - 2);

	// i = pos;
	// ft_printf("%s", ESC_LEFT);
	// while (i++ <= len)
	// 	write(1, " ", 1);
	ft_printf("\r");
	i = 9;
	while (i--)
		ft_printf("%s", ESC_RIGHT);
	i = -1;
	while (++i < len)
		write(1, " ", 1);

	move_cursor(ws, len - 3);
}

void    print_buffer_actual_2(char *buff, ssize_t len, int pos, struct winsize *ws)
{
	ssize_t	i;
	
	clear_line_2(pos, len + 1, ws);

	// i = pos - 2;
	// while (++i < len && buff[i])
	// 	ft_printf("%c", buff[i]);
	ft_printf("\r");
	i = -1;
	i = 9;
	while (i--)
		ft_printf("%s", ESC_RIGHT);
	while (++i < len)
		ft_printf("%c", buff[i]);
	while (--len >= pos && len >= 0)
		ft_printf("%s", ESC_LEFT);
}

// char	*get_cmd_2(int fd)
// {
// 	static struct termios oldt;

// 	init_term(&oldt);

// 	char c;
// 	char esc[3];
// 	char *buff;
// 	int pos;
// 	ssize_t len;

// 	struct winsize ws;
// 	ioctl(1, TIOCGSIZE, &ws);

// 	buff = ft_strnew(HIST_BUFF_LEN);

// 	pos = 0;
// 	len = 0;
// 	esc[0] = ESC;

// 	while (read(fd, &c, 1) > 0)
// 	{
// 		if (c == 4 && ft_strlen(buff) == 0)
// 		{
// 			buff[0] = '\x04';
// 			buff[1] = '\0';
// 			break ;
// 		}
// 		else if (c == '\n')
// 		{
// 			ft_printf("\n");
// 			break ;
// 		}
// 		// else if (c == DEL)
// 		// {
// 		// 	backspace(buff, &pos, &len);
// 		// 	print_buffer_actual_2(buff, len, pos, &ws);
// 		// }
// 		// else if (c == ESC)
// 		// {
// 		// 	read(1, &esc[1], 2);
// 		// 	// check_escape_ctrl(esc);
// 		// 	check_escape_line(esc, buff, &pos, &ws);
// 		// }
// 		// else if (ft_isprint(c))
// 		// {
// 		// 	update_buffer(c, buff, &pos, &len);
// 		// 	print_buffer_actual_2(buff, len, pos, &ws);
// 		// }
// 		// check_length_buffer(current);
// 		if ((ft_strlen(buff) + 7) % ws.ws_col == 0)
// 			ft_printf("\n");
// 		if (DEBUG)
// 			if (c == '\t')
// 				exit(1);
// 	}

	
// 	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
// 	return (buff);
// }

char		*get_txt(char *word, int i)
{
	char	*bufer;
	char	*res;
	char	*help;

	res = ft_strnew(1);
	help = ft_strnew(1);
	while (1)
	{
		ft_printf("%sheredoc> %s", CLR_RED, CLR_RESET);
		// bufer = get_cmd_2(0);
		bufer = get_cm(0, 0, 1, 1024);
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
