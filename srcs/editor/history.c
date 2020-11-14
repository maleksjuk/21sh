/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:48:11 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/14 21:08:35 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		check_escape_line(char *escape, char *buff, int *i)
{
	if (ft_strnequ(escape, ESC_LEFT, 3) && *i > 0)
	{
		(*i)--;
		ft_printf("%s", ESC_LEFT);
		return (1);
	}
	else if (ft_strnequ(escape, ESC_RIGHT, 3) && buff[*i] != '\0')
	{
		(*i)++;
		ft_printf("%s", ESC_RIGHT);
		return (1);
	}
	return (0);
}

t_history	*check_escape_history(char *escape, char *buff, int *i, t_history *current)
{
	if (current && ft_strnequ(escape, ESC_UP, 3) && current->prev)
		current = current->prev;
	else if (current && ft_strnequ(escape, ESC_DOWN, 3) && current->next)
		current = current->next;
	else
		return (current);

	ft_printf("\r");
	print_prompt();
	*i = -1;
	while (buff[++(*i)])
		write(1, " ", 1);
	ft_printf("\r");
	print_prompt();
	*i = ft_strlen(current->buff);
	ft_printf("%s", current->buff);

	return (current);
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
			last->buff = ft_strnew((size_t)sizeof(current->buff));
			ft_strcpy(last->buff, current->buff);
		}
	}

	if (DEBUG && current)
		ft_printf("\n%swrite to history: |%s|%s", CLR_CYAN, current->buff, CLR_RESET);
	
	while (current && current->next)
		current = current->next;

	new = (t_history *)malloc(sizeof(t_history));
	new->count = 1;
	new->buff = ft_strnew(BUFF_LEN);
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

	if (hist->count * BUFF_LEN - ft_strlen(hist->buff) > 3)
		return ;
	hist->count++;
	tmp = ft_strnew(BUFF_LEN * hist->count);
	strcpy(tmp, hist->buff);
	free(hist->buff);
	hist->buff = tmp;
}

void	reset_history(t_history *hist)
{
	while (hist && hist->prev)
		hist = hist->prev;
	while (hist && hist->next)
	{
		if (!ft_strequ(hist->buff, hist->save))
		{
			if (hist->buff)
				free(hist->buff);
			hist->buff = ft_strnew(BUFF_LEN * hist->count);
			// if (!hist->buff)
			// 	hist->buff = ft_strnew(BUFF_LEN * hist->count);
			// ft_memset(hist->buff, 0, sizeof(hist->buff));
			ft_strcpy(hist->buff, hist->save);
		}
		hist = hist->next;
	}
}
