# include <stdio.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
// #include "../libftprintf/includes/libft.h"
// #include "../includes/minishell.h"

# define KEY_RIGHT_ "\x1b\x5b\x43\x0\x0\x0"
# define KEY_LEFT_  "\x1b\x5b\x44\x0\x0\x0"
# define KEY_UP_    "\x1b\x5b\x41\x0\x0\x0"
# define KEY_DOWN_  "\x1b\x5b\x42\x0\x0\x0"

# define MSH_HISTORY ".msh_history"
# define HISTORY_LIMIT 50

typedef struct 	s_history
{
	char		*buff;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

int	len_tmp(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && ++i < n)
	{
		if (*s1 == '\0' && *s2 == '\0')
			return (1);
		if (*s1 == '\0' || *s2 == '\0')
			return (0);
		s1++;
		s2++;
	}
	if (n == 0 || *s1 == *s2)
		return (1);
	return (0);
}

char	*new_str(int len)
{
	char	*buff;
	int		i;

	buff = (char *)malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	i = 0;
	while (i < len + 1)
		buff[i++] = '\0';
	return (buff);
}


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

int	get_max(char *buff, char *hist)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i])
		i++;
	while (buff[j])
		j++;
	return (i > j ? i : j);
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
	{
		write(1, " ", 1);
		buff[*i] = '\0';
	}
	write(1, "\r", 1);
	strcpy(buff, current->buff);
	*i = len_tmp(buff);
	write(1, buff, *i);

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
		else
			write(1, " ", 1);
	write(1, "\r", 1);
	i = -1;
	while (++i < pos)
		write(1, &buff[i], 1);
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
// 		line = new_str(255);
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
// 				line = new_str(255);
// 				// i = 0;
// 			}
// 			else
// 				line[i++] = c;
// 		}
// 	}
// 	return (history);
// }

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
	char *reserve;
	int pos;
	int len;
	int i;

	t_history	*history;
	// history = init_history();
	history = NULL;

	buff = new_str(255);
	escape = new_str(3);
	reserve = new_str(255);

	pos = 0;
	while (read(1, &c, 1) > 0 && len < 255 && c != '\t')
	{
		if (c == '\n')
		{
			if (len_tmp(buff) == 0)
			{
				write(1, "\n", 1);
				continue ;
			}
			history = new_history(history, buff);
			free(buff);
			buff = new_str(255);
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
				history = check_escape_history(escape, buff, &pos, history);
		}
	}
	printf("\n|-----EOF-----|\n");
	printf("buff: |%s|\n", buff);

	while (history && history->prev)
		history = history->prev;
	printf("history:\n");
	while (history && history->next)
	{
		printf("|%s|\n", history->buff);
		free(history->buff);
		history = history->next;
		free(history->prev);
	}
	if (history)
	{
		printf("|%s|\n", history->buff);
		free(history->buff);
		free(history);
	}

	free(buff);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}

