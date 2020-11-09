#include "tmp.h"

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

void print_buffer_actual(char *buff, int len, int pos)
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
	int	i;

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
	int	i;

	i = *len + 1;
	while (--i > *pos)
		buff[i] = buff[i - 1];
	buff[(*pos)++] = c;
	(*len)++;
}

void	update_escape(char c, char *escape)
{
	escape[0] = escape[1];
	escape[1] = escape[2];
	escape[2] = c;
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
