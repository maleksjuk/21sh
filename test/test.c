#include "tmp.h"

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

	last = new_history(NULL, NULL);
	current = last;
	buff = current->buff;

	pos = 0;

	write(1, "--> ", 4);
	while (read(1, &c, 1) > 0 && len < BUFF_LEN - 1 && c != '\t')
	{
		if (c == '\n')
		{
			write(1, "\n", 1);
			if (len_tmp(buff) == 0)
				continue ;
			
			last = new_history(current, last);
			buff = last->buff;

			reset_history(last->prev);
			current = last;
			
			pos = 0;
			write(1, "--> ", 4);
		}
		else if (c == 127)
		{
			backspace(buff, &pos, &len);
			print_buffer_actual(buff, len, pos);
		}
		else if (c == 27)
		{
			escape[0] = c;
			read(1, &escape[1], 1);
			read(1, &escape[2], 1);
			if (!check_escape_line(escape, buff, &pos))
				current = check_escape_history(escape, buff, &pos, current);
			buff = current->buff;
		}
		else
		{
			update_buffer(c, buff, &pos, &len);
			print_buffer_actual(buff, len, pos);
		}
		check_length_buffer(current);
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
			printf("|%s|", current->save);
			free(current->save);
		}
		if (current->buff)
		{
			printf("--|%s|", current->buff);
			free(current->buff);
		}
		printf("\n");
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
		if (current->buff)
		{
			printf("--|%s|", current->buff);
			free(current->buff);
		}
		printf("\n");
		free(current);
	}

	free(escape);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}

