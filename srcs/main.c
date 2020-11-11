/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/11 20:20:11 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "editor.h"

void	cmd_input(char *bufer, t_env *env)
{
	char	**cmd_list;
	int		i;

	cmd_list = ft_strsplit(bufer, ';');
	i = 0;
	while (cmd_list[i])
	{
		if (!redirection(cmd_list[i]))
			cmd_processing(cmd_list[i], env);
		free(cmd_list[i]);
		i++;
	}
	free(cmd_list);
}

char	*get_cmd(int fd)
{
	char	*bufer;
	int		buf_size;
	char	smbl[1];
	int		i;
	char	*overflow;

	buf_size = 1024;
	bufer = ft_strnew(buf_size);
	i = 0;
	while (read(fd, smbl, 1) > 0)
	{
		if (*smbl == '\n')
			break ;
		bufer[i++] = smbl[0];
		if (i == buf_size)
		{
			buf_size *= 2;
			overflow = ft_strnew(buf_size);
			ft_strncpy(overflow, bufer, i);
			free(bufer);
			bufer = overflow;
		}
	}
	return (bufer);
}


char	*get_cmd_2(int fd)
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
	// int i;

	escape = new_str(3);

	t_history	*current;
	static t_history	*last;

	last = new_history(NULL, NULL);
	current = last;
	buff = current->buff;

	pos = 0;
	while (read(fd, &c, 1) > 0 && len < BUFF_LEN - 1)
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
			break;
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
	// printf("\n|-----EOF-----|\n");
	// printf("buff: |%s|\n", buff);

	// while (current && current->prev)
	// 	current = current->prev;
	// printf("history:\n");
	// while (current && current->next)
	// {
	// 	if (current->save)
	// 	{
	// 		printf("|%s|", current->save);
	// 		free(current->save);
	// 	}
	// 	if (current->buff)
	// 	{
	// 		printf("--|%s|", current->buff);
	// 		free(current->buff);
	// 	}
	// 	printf("\n");
	// 	current = current->next;
	// 	free(current->prev);
	// }
	// if (current)
	// {
	// 	if (current->save)
	// 	{
	// 		printf("|%s|\n", current->save);
	// 		free(current->save);
	// 	}
	// 	if (current->buff)
	// 	{
	// 		printf("--|%s|", current->buff);
	// 		free(current->buff);
	// 	}
	// 	printf("\n");
	// 	free(current);
	// }

	free(escape);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return (buff);
}


int		main(int argc, char **argv, char **envp)
{
	char	*bufer;

	g_env = get_env(envp);
	if (!g_env)
		return (error_message("error", "null env"));
	update_lvl();
	ft_printf("\033[1;7;32m* * * 21SH [start] * * *\033[0m\n");
	while (1)
	{
		signals();
		print_prompt();
		bufer = get_cmd(0);
		if (!ft_strequ(bufer, ""))
			cmd_input(bufer, g_env);
		free(bufer);
	}
	return (0);
	(void)argc;
	(void)argv;
}
