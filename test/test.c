# include <stdio.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

# define KEY_RIGHT_ "\x1b\x5b\x43\x0\x0\x0"
# define KEY_LEFT_  "\x1b\x5b\x44\x0\x0\x0"
# define KEY_UP_    "\x1b\x5b\x41\x0\x0\x0"
# define KEY_DOWN_  "\x1b\x5b\x42\x0\x0\x0"

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
	if (ft_strnequ(escape, KEY_UP_, 3))
	{
		if (current->prev)
			current = current->prev;
		write(1, " ", len_tmp(buff));
		write(1, "\r", 1);
		memset(buff, '\0', len_tmp(buff));
		buff = strcpy(buff, current->buff);
		*i = len_tmp(buff);
		write(1, buff, *i);
	}
	else if (ft_strnequ(escape, KEY_DOWN_, 3))
	{
		if (current->next)
			current = current->next;
		else
			return (current);
		write(1, " ", len_tmp(buff));
		memset(buff, '\0', len_tmp(buff));
		buff = strcpy(buff, current->buff);
		*i = len_tmp(buff);
		write(1, buff, *i);
	}
	return (current);
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

void print_bufer_actual(char *buff, int len, int pos)
{
	int	i;

	i = pos - 2;
	while (++i < len)
		write(1, &buff[i], 1);
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

	printf("\nnew history buff: |%s|\n", new->buff);
	
	return (new);
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

	t_history	*history;
	history = NULL;

	buff = new_str(255);
	escape = new_str(3);
	reserve = new_str(255);

	pos = 0;
	while (read(1, &c, 1) > 0 && len < 255 && c != '\t')
	{
		update_escape(c, escape);

		if (c == '\n')
		{
			history = new_history(history, buff);
			free(buff);
			buff = new_str(255);
			pos = 0;
		}
		else if (!(escape[0] == 27 || escape[1] == 27 || escape[2] == 27))
		{
			update_buffer(c, buff, &pos, &len);
			print_bufer_actual(buff, len, pos);
		}
		else
		{
			if (!check_escape_line(escape, buff, &pos))
				history = check_escape_history(escape, buff, &pos, history);
		}
	}
	printf("\n|-----EOF-----|\n");
	printf("buff: |%s|\n", buff);

	while (history->prev)
		history = history->prev;
	printf("history:\n");
	while (history->next)
	{
		printf("|%s|\n", history->buff);
		free(history->buff);
		history = history->next;
		free(history->prev);
	}
	free(history->buff);
	free(history);

	free(buff);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}

