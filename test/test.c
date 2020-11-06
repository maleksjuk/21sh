# include <stdio.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

#include "tmp.h"

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

t_history	*new_history(t_history *current, char *buff)
{
	t_history	*new;
	int i = -1;
	int fd;

	if (current)
		while (current->next)
			current = current->next;
	new = (t_history *)malloc(sizeof(t_history));
	new->buff = new_str(len_tmp(buff));
	while (buff[++i])
		new->buff[i] = buff[i];
	if (current)
	{
		new->prev = current;
		current->next = new;
	}
	else
		new->prev = NULL;
	new->next = NULL;

	fd = open(MSH_HISTORY, O_APPEND | O_RDWR | O_CREAT, 0644);
	write(fd, "\n", 1);
	write(fd, new->buff, len_tmp(new->buff));
	close(fd);

	printf("\nnew history buff: |%s|\n", new->buff);
	
	return (new);
}

t_history	*history_line(t_history *current, t_history *last)
{
	t_history	*new;
	int fd;

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

	if (current)
	{
		fd = open(MSH_HISTORY, O_APPEND | O_RDWR | O_CREAT, 0644);
		write(fd, current->buff, len_tmp(current->buff));
		write(fd, "\n", 1);
		close(fd);

		printf("write to history: |%s|\n", current->buff);

		while (current->next)
			current = current->next;
	}

	new = (t_history *)malloc(sizeof(t_history));
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

// t_history	*init_history()
// {
// 	int			fd;
// 	t_history	*history;
// 	char		*line;
// 	char		c;
// 	int			i;

// 	history = NULL;
// 	if (access(MSH_HISTORY, F_OK) != -1 )
// 	{
// 		line = new_str(BUFF_LEN);
// 		i = 0;
// 		fd = open(MSH_HISTORY, O_RDONLY);
// 		while (read(fd, &c, 1) > 0)
// 		{
// 			if (c == '\n'
// 				 && (i = 0)
// 				)
// 			{
// 				history = new_history(history, line);
// 				free(line);
// 				line = new_str(BUFF_LEN);
// 				// i = 0;
// 			}
// 			else
// 				line[i++] = c;
// 		}
// 	}
// 	return (history);
// }

void	update_history(t_history *history)
{
	int	i;

	while (history)
	{
		free(history->buff);
		history->buff = new_str(BUFF_LEN);
		strcpy(history->buff, history->save);
		history = history->prev;
	}
}

int main(void)
{ 
	static struct termios oldt;
	static struct termios newt;
	
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHOCTL | ECHO);
	newt.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	char c;
	char *escape;
	char *buff;
	int pos;
	int len;
	int i;

	escape = new_str(3);

	t_history	*current;
	t_history	*last;

	// last = init_history();

	last = history_line(NULL, NULL);
	current = last;
	buff = current->buff;

	pos = 0;
	while (read(1, &c, 1) > 0 && len < BUFF_LEN - 1 && c != '\t')
	{
		if (c == '\n')
		{
			write(1, "\n", 1);
			if (len_tmp(buff) == 0)
				continue ;
			
			last = history_line(current, last);
			buff = last->buff;

			update_history(last->prev);
			current = last;
			
			pos = 0;
		}
		else if (c == 127)
		{
			backspace(buff, &pos, &len);
			print_buffer_actual(buff, len, pos);
		}
		else if (c != 27)
		{
			update_buffer(c, buff, &pos, &len);
			print_buffer_actual(buff, len, pos);
		}
		else
		{
			escape[0] = c;
			read(1, &escape[1], 1);
			read(1, &escape[2], 1);
			if (!check_escape_line(escape, buff, &pos))
				current = check_escape_history(escape, buff, &pos, current);
			buff = current->buff;
		}
	}
	printf("\n|-----EOF-----|\n");
	printf("buff: |%s|\n", buff);

	while (current && current->prev)
		current = current->prev;
	printf("history:\n");
	while (current && current->next)
	{
		if (current->save)
		{
			printf("|%s|\n", current->save);
			free(current->save);
		}
		free(current->buff);
		current = current->next;
		free(current->prev);
	}
	if (current)
	{
		if (current->save)
		{
			printf("|%s|\n", current->save);
			free(current->save);
		}
		free(current->buff);
		free(current);
	}

	free(escape);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}

