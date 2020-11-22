/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:52:45 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/11/22 19:45:16 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "editor.h"

void		check_esca(t_reader *rdr)
{
	int	i;

	i = 1;
	rdr->height = (ft_strlen(rdr->buff) + 9) / rdr->ws.ws_col;
	rdr->curs_pos[0] = (rdr->pos + 9) % rdr->ws.ws_col;
	rdr->curs_pos[1] = (rdr->pos + 9) / rdr->ws.ws_col;
	while (!ft_isalpha(rdr->esc[i - 1]))
		read(rdr->fd, &rdr->esc[i++], 1);
	rdr->esc[i] = '\0';
	if (ft_strnequ(rdr->esc, ESC_HOME, 3))
		rdr->c = CTRL_A;
	else if (ft_strnequ(rdr->esc, ESC_END, 3))
		rdr->c = CTRL_E;
	else if (check_escape_ctrl(rdr))
		return ;
	else if (check_escape_line(rdr))
		return ;
}

// void		move_cursor_2(struct winsize ws, int pos)
// {
// 	int	i;

// 	if (!ws.ws_col)
// 		return ;
// 	i = (pos + 9) / ws.ws_col;
// 	if (!i)
// 		return ;
// 	while (i-- > 0)
// 		ft_printf("%s", ESC_UP);
// 	ft_printf("\r");
// }

// void		clear_line_2(t_reader *rdr, int identi)
// {
// 	ssize_t	i;

// 	move_cursor_2(rdr->ws, rdr->len - 2);
// 	ft_printf("\r");
// 	if (identi == 3)
// 		ft_printf("%sheredoc> %s", CLR_RED, CLR_RESET);
// 	else if (identi == 2)
// 		ft_printf("%sdquotes> %s", CLR_RED, CLR_RESET);
// 	else if (identi == 1)
// 		ft_printf("%suquotes> %s", CLR_RED, CLR_RESET);
// 	i = 0;
// 	while (++i < rdr->len)
// 		write(1, " ", 1);
// 	move_cursor_2(rdr->ws, rdr->len - 2);
// }

void		print_buffer_actual_2(t_reader *rdr, int identi)
{
	ssize_t	i;

	// clear_line_2(rdr, identi);
	// ft_printf("\r");
	i = 0;
	(void)identi;
	// if (identi == 3)
	// 	ft_printf("%sheredoc> %s", CLR_RED, CLR_RESET);
	// else if (identi == 2)
	// 	ft_printf("%sdquotes> %s", CLR_RED, CLR_RESET);
	// else if (identi == 1)
	// 	ft_printf("%suquotes> %s", CLR_RED, CLR_RESET);
	ft_putstr_fd(tgetstr(TERM_CLEAR, NULL), g_term->fd);
	i = rdr->pos - 1;
	while (i < rdr->len)
		ft_printf("%c", rdr->buff[i++]);
	if ((rdr->pos + 9) % rdr->ws.ws_col == 0)
		ft_putstr_fd(tgetstr(TERM_DOWN, NULL), g_term->fd);
	i = rdr->len;
	while (--i >= rdr->pos && i >= 0)
		ft_printf("%s", ESC_LEFT);
}

int			specials(t_reader *rdr, int i, int identi)
{
	if (rdr->c == CTRL_D && ft_strlen(rdr->buff) == 0)
		ft_strcpy(rdr->buff, "\x04");
	else if (rdr->c == CTRL_C)
		ft_strcpy(rdr->buff, "\x03");
	else if (rdr->c == CTRL_A || rdr->c == CTRL_E)
	{
		ft_strcpy(rdr->esc, rdr->c == CTRL_A ? ESC_CTRL_UP : ESC_CTRL_DOWN);
		i = rdr->len / rdr->ws.ws_col + 1;
		while (i--)
			check_escape_ctrl(rdr);
	}
	else if (rdr->c == DEL)
	{
		if (backspace(rdr))
		{
			ft_putstr_fd(tgetstr("kb", NULL), g_term->fd);
			ft_putstr_fd(tgetstr("dc", NULL), g_term->fd);
		}
		(void)identi;
		i = 0;
	}
	else
		i = 0;
	return (i);
}

int			check_n(t_reader *rdr)
{
	if (rdr->c != '\n')
		return (0);
	return (1);
}

char		*mega_read(int fd, int identi)
{
	t_reader	*rdr;

	rdr = set_reader(fd, NULL);
	while (read(rdr->fd, &rdr->c, 1) > 0)
	{
		if (check_n(rdr))
			break ;
		else if (rdr->c == ESC)
			check_esca(rdr);
		else if (ft_isprint(rdr->c))
		{
			update_buffer(rdr);
			print_buffer_actual_2(rdr, identi);
		}
		if (specials(rdr, 1, identi) > 0)
			break ;
	}
	ft_printf("\n");
	return (unset_reader(rdr));
	(void)identi;
}

char		*get_txt(char *word, int i, char *help)
{
	char	*bufer;
	char	*res;

	res = ft_strnew(1);
	while (1)
	{
		ft_printf("%sheredoc> %s", CLR_RED, CLR_RESET);
		bufer = mega_read(0, 3);
		if (ft_strequ(bufer, word) || ft_strequ(bufer, "\x04"))
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
