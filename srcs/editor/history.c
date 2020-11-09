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

#include "../../includes/editor.h"

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
