/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:48:11 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/25 20:35:18 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_history	*init_new_history(void)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	new->count = 1;
	new->buff = ft_strnew(HIST_BUFF_LEN);
	new->save = NULL;
	return (new);
}

t_history	*new_history(t_history *current, t_history *last)
{
	t_history	*new;

	if (last)
	{
		last->save = ft_strnew(ft_strlen(current->buff) + 1);
		ft_strcpy(last->save, current->buff);
		if (last != current)
		{
			if (last->count != current->count)
			{
				free(last->buff);
				last->buff = ft_strnew((size_t)current->count * HIST_BUFF_LEN);
				last->count = current->count;
			}
			ft_strcpy(last->buff, current->buff);
		}
	}
	while (current && current->next)
		current = current->next;
	new = init_new_history();
	if (current)
	{
		new->prev = current;
		current->next = new;
	}
	else
		new->prev = NULL;
	new->next = NULL;
	return (new);
}

void		check_length_buffer(t_history *hist, ssize_t len)
{
	char	*new_buff;

	if (hist->count * HIST_BUFF_LEN > len + 10)
		return ;
	hist->count++;
	new_buff = ft_strnew(HIST_BUFF_LEN * hist->count);
	ft_strcpy(new_buff, hist->buff);
	free(hist->buff);
	hist->buff = new_buff;
}

void		reset_history(t_history *hist)
{
	while (hist && hist->prev)
		hist = hist->prev;
	while (hist && hist->next)
	{
		if (!ft_strequ(hist->buff, hist->save))
		{
			ft_memset(hist->buff, 0, HIST_BUFF_LEN * hist->count);
			ft_strcpy(hist->buff, hist->save);
		}
		hist = hist->next;
	}
}
