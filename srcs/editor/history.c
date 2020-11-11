/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:48:11 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/09 21:56:52 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		check_escape_line(char *escape, char *buff, int *i)
{
	if (ft_strnequ(escape, KEY_LEFT_, 3) && *i > 0)
	{
		(*i)--;
		write(1, KEY_LEFT_, 3);
		return (1);
	}
	else if (ft_strnequ(escape, KEY_RIGHT_, 3) && buff[*i] != '\0')
	{
		(*i)++;
		write(1, KEY_RIGHT_, 3);
		return (1);
	}
	return (0);
}

t_history	*check_escape_history(char *escape, char *buff, int *i, t_history *current)
{
	if (current && ft_strnequ(escape, KEY_UP_, 3))
	{
		if (current->prev)
			current = current->prev;
		else
			return (current);
	}
	else if (current && ft_strnequ(escape, KEY_DOWN_, 3))
	{
		if (current->next)
			current = current->next;
		else
			return (current);
	}
	else
		return (current);

	write(1, "\r", 1);
	*i = -1;
	while (buff[++(*i)])
		write(1, " ", 1);
	write(1, "\r", 1);
	*i = len_tmp(current->buff);
	write(1, current->buff, *i);

	return (current);
}

void	backspace(char *buff, int *pos, int *len)
{
	int	i;

	if (*pos == 0)
		return ;
	i = *pos - 1;
	while (++i <= *len)
		buff[i - 1] = buff[i];
	buff[--(*len)] = '\0';
	(*pos)--;
}

t_history	*new_history(t_history *current, t_history *last)
{
	t_history	*new;

	if (last)
	{
		last->save = new_str(len_tmp(current->buff) + 1);
		strcpy(last->save, current->buff);

		if (last != current)
		{
			last->buff = new_str(BUFF_LEN);
			strcpy(last->buff, current->buff);
		}
	}

	// if (current)
	//	printf("write to history: |%s|\n", current->buff);
	while (current && current->next)
		current = current->next;

	new = (t_history *)malloc(sizeof(t_history));
	new->count = 1;
	new->buff = new_str(BUFF_LEN);
	new->save = NULL;

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

void	check_length_buffer(t_history *hist)
{
	char	*tmp;

	if (hist->count * BUFF_LEN - len_tmp(hist->buff) > 3)
		return ;
	hist->count++;
	tmp = new_str(BUFF_LEN * hist->count);
	strcpy(tmp, hist->buff);
	free(hist->buff);
	hist->buff = tmp;
}
