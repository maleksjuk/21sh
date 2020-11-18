/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:48:11 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/18 16:43:17 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		check_escape_ctrl_horizont(char *escape, char *buff, int *i, struct winsize *ws)
{
	int	height;
	int	pos[2];

	height = (ft_strlen(buff) + 7) / ws->ws_col;
	pos[0] = (*i + 7) % ws->ws_col;
	pos[1] = (*i + 7) / ws->ws_col;
	if (ft_strnequ(escape, ESC_CTRL_LEFT, 6))
	{
		while (buff && *i > 0)
		{	
			(*i)--;
			pos[0]--;
			ft_printf("%s", ESC_LEFT);
			
			if (pos[0] < 0 && pos[1] > 0)
			{
				// ft_printf("%s", ESC_UP);
				while (pos[0] < ws->ws_col - 1)
				{
					pos[0]++;
					ft_printf("%s", ESC_RIGHT);
				}
				pos[1]--;
			}
			if (!(*i == ft_strlen(buff) || buff[*i] != ' '))
				break ;
		}
		return (1);
	}
	else if (ft_strnequ(escape, ESC_CTRL_RIGHT, 6))
	{
		while (buff && *i < ft_strlen(buff))
		{
			(*i)++;
			ft_printf("%s", ESC_RIGHT);
			if (pos[0] == ws->ws_col - 1 && pos[1] < height)
			{
				ft_printf("%s\r", ESC_DOWN);
				pos[1]++;
			}
			pos[0]++;
			if (!buff[*i] || buff[*i] == ' ')
				break ;
		}
		return (1);
	}
	return (0);
}

int		check_escape_ctrl_vertical(char *escape, char *buff, int *i, struct winsize *ws)
{
	int	height;
	int	swap;
	int	pos[2];

	height = (ft_strlen(buff) + 7) / ws->ws_col;
	pos[0] = (*i + 7) % ws->ws_col;
	pos[1] = (*i + 7) / ws->ws_col;
	swap = 0;
	if (ft_strnequ(escape, ESC_CTRL_UP, 6))
	{
		if (height > 0 && pos[1] > 0)
		{
			while (*i > 0 && swap < ws->ws_col)
			{
				swap++;
				(*i)--;
			}
			ft_printf("%s", ESC_UP);
		}
		else
		{
			while (*i > 0)
			{
				(*i)--;
				ft_printf("%s", ESC_LEFT);
			}
		}
		if (pos[1] == 0 || pos[1] == 1)
		{
			ft_printf("\r");
			print_prompt();
		}
		return (1);
	}
	else if (ft_strnequ(escape, ESC_CTRL_DOWN, 6))
	{
		if (height > 0 && pos[1] < height)
		{
			while (buff[*i] && swap < ws->ws_col)
			{
				swap++;
				(*i)++;
			}
			ft_printf("%s", ESC_DOWN);
		}
		else
		{
			while (buff[*i])
			{
				(*i)++;
				ft_printf("%s", ESC_RIGHT);
			}
		}
		if (pos[1] == height - 1 || pos[1] == height)
		{
			ft_printf("\r");
			pos[0] = (ft_strlen(buff) + 7) % ws->ws_col;
			while (pos[0]--)
				ft_printf("%s", ESC_RIGHT);
		}
		return (1);
	}
	return (0);
}

int		check_escape_ctrl(char *escape, char *buff, int *i, struct winsize *ws)
{
	if (check_escape_ctrl_horizont(escape, buff, i, ws))
		return (1);
	if (check_escape_ctrl_vertical(escape, buff, i, ws))
		return (1);
	return (0);
}

int		check_escape_line(char *escape, char *buff, int *i, struct winsize *ws)
{
	int	height;
	int	pos[2];

	height = (ft_strlen(buff) + 7) / ws->ws_col;
	pos[0] = (*i + 7) % ws->ws_col;
	// pos[1] = (*i + 7) / ws->ws_col;
	if (ft_strnequ(escape, ESC_LEFT, 3) && *i > 0)
	{
		(*i)--;
		ft_printf("%s", ESC_LEFT);
		return (1);
	}
	else if (ft_strnequ(escape, ESC_RIGHT, 3) && buff[*i] != '\0')
	{
		(*i)++;
		if (pos[0] == ws->ws_col - 1)
			ft_printf("%s\r", ESC_DOWN);
		else
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
			last->buff = ft_strnew(ft_strlen(current->buff) + 10);
			ft_strcpy(last->buff, current->buff);
		}
	}

	if (DEBUG && current)
		ft_printf("\n%swrite to history: |%s|%s", CLR_CYAN, current->buff, CLR_RESET);
	
	while (current && current->next)
		current = current->next;

	new = (t_history *)malloc(sizeof(t_history));
	new->count = 1;
	new->buff = ft_strnew(HIST_BUFF_LEN);
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
// , struct winsize *ws_curr)
{
	char	*tmp;

	// ws_curr->ws_col = ft_strlen(hist->)

	if (hist->count * HIST_BUFF_LEN - ft_strlen(hist->buff) > 10)
		return ;
	hist->count++;
	tmp = ft_strnew(HIST_BUFF_LEN * hist->count);
	ft_strcpy(tmp, hist->buff);
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
			hist->buff = ft_strnew(HIST_BUFF_LEN * hist->count);
			// if (!hist->buff)
			// 	hist->buff = ft_strnew(HIST_BUFF_LEN * hist->count);
			// ft_memset(hist->buff, 0, sizeof(hist->buff));
			ft_strcpy(hist->buff, hist->save);
		}
		hist = hist->next;
	}
}
