/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 06:17:35 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/25 21:28:04 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		sh_cut(t_reader *rdr)
{
	int	i;

	if (g_term->clip)
		free(g_term->clip);
	g_term->clip = ft_strdup(&rdr->buff[rdr->pos]);
	i = rdr->pos - 1;
	while (++i < rdr->len)
		rdr->buff[i] = 0;
	rdr->len = rdr->pos;
	ft_putstr_fd(tgetstr(TERM_CLEAR, NULL), g_term->fd);
}

void		sh_copy(t_reader *rdr)
{
	if (g_term->clip)
		free(g_term->clip);
	g_term->clip = ft_strdup(&rdr->buff[rdr->pos]);
}

void		sh_paste(t_reader *rdr, t_history *current)
{
	char	*new_buff;
	char	*paste;

	if (!g_term->clip)
		return ;
	paste = ft_strjoin(g_term->clip, &rdr->buff[rdr->pos]);
	rdr->buff[rdr->pos] = '\0';
	if (ft_strlen(rdr->buff) + ft_strlen(paste) + 3 >
		(size_t)(current->count * HIST_BUFF_LEN))
	{
		current->count++;
		new_buff = ft_strnew(ft_strlen(rdr->buff) + ft_strlen(paste) + 10);
		ft_strcpy(new_buff, rdr->buff);
		ft_strcpy(&new_buff[ft_strlen(new_buff)], paste);
		free(current->buff);
		current->buff = new_buff;
		rdr->buff = current->buff;
	}
	else
		ft_strcpy(&rdr->buff[rdr->pos], paste);
	free(paste);
	if (rdr->pos)
		ft_putstr_fd(tgetstr(TERM_LEFT, NULL), g_term->fd);
	rdr->len += ft_strlen(g_term->clip);
	print_buffer_actual(rdr);
}

void		sh_paste_heredoc(t_reader *rdr)
{
	char	*new_buff;
	char	*paste;

	if (!g_term->clip)
		return ;
	paste = ft_strjoin(g_term->clip, &rdr->buff[rdr->pos]);
	rdr->buff[rdr->pos] = '\0';
	if (ft_strlen(rdr->buff) + ft_strlen(paste) + 3 > rdr->buff_len)
	{
		new_buff = ft_strnew(ft_strlen(rdr->buff) + ft_strlen(paste) + 10);
		ft_strcpy(new_buff, rdr->buff);
		ft_strcpy(&new_buff[ft_strlen(new_buff)], paste);
	}
	else
		ft_strcpy(&rdr->buff[rdr->pos], paste);
	free(paste);
	if (rdr->pos)
		ft_putstr_fd(tgetstr(TERM_LEFT, NULL), g_term->fd);
	rdr->len += ft_strlen(g_term->clip);
	print_buffer_actual(rdr);
}

int			cut_copy_paste(t_reader *rdr, t_history *current)
{
	char	opt[4];

	if (rdr->c != '\xe2')
		return (0);
	opt[0] = '\xe2';
	read(rdr->fd, &opt[1], 1);
	if (opt[1] != '\x88')
		return (0);
	read(rdr->fd, &opt[2], 1);
	if (ft_strnequ(opt, OPT_V, 3))
		sh_copy(rdr);
	else if (ft_strnequ(opt, OPT_D, 3))
		sh_cut(rdr);
	else if (ft_strnequ(opt, OPT_B, 3))
	{
		if (current)
			sh_paste(rdr, current);
		else
			sh_paste_heredoc(rdr);
	}
	else
		return (0);
	return (1);
}
