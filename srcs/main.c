/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/14 20:49:10 by obanshee         ###   ########.fr       */
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
	static struct termios oldt;
	static struct termios newt;
	
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHOCTL | ECHO);
	newt.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	char c;
	char esc[3];
	char *buff;
	int pos;
	int len;

	t_history	*current;

	if (!g_hist)
		g_hist = new_history(NULL, NULL);
	current = g_hist;
	buff = current->buff;

	pos = 0;
	len = 0;
	esc[0] = ESC;

	while (read(fd, &c, 1) > 0)
	{
		if (c == 4 && ft_strlen(buff) == 0)
			return ("\x04");
		else if (c == '\n')
		{
			if (ft_strlen(buff) != 0)
			{
				g_hist = new_history(current, g_hist);
				buff = g_hist->prev->buff;
				reset_history(current);
			}
			break ;
		}
		else if (c == DEL)
		{
			backspace(buff, &pos, &len);
			print_buffer_actual(buff, len, pos);
		}
		else if (c == ESC)
		{
			read(1, &esc[1], 2);
			if (!check_escape_line(esc, buff, &pos))
				current = check_escape_history(esc, buff, &pos, current);
			buff = current->buff;
		}
		else if (ft_isprint(c))
		{
			update_buffer(c, buff, &pos, &len);
			print_buffer_actual(buff, len, pos);
		}
		check_length_buffer(current);
		if (DEBUG)
			if (c == '\t')
				exit(1);
	}

	if (DEBUG)
	{
		while (current->prev)
			current = current->prev;
		while (current->next)
		{
			ft_printf("\n%sHIST: |[%p] - b[%s] - s[%s]|%s", CLR_YELLOW, current->buff, current->buff, current->save, CLR_RESET);
			current = current->next;
		}
	}

	ft_printf("\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (buff);
}


int		main(int argc, char **argv, char **envp)
{
	char	*buff;

	g_env = get_env(envp);
	if (!g_env)
		return (error_message("error", "null env"));
	g_hist = NULL;
	update_lvl();
	ft_printf("%s%s%s* * * 21SH [start] * * *%s\n", CLR_BOLD, CLR_GREEN, CLR_INVERSE, CLR_RESET);
	while (21)
	{
		signals();
		print_prompt();
		buff = get_cmd(0);
		if (ft_strequ(buff, "\x04"))
			cmd_exit("exit 0");
		
		if (DEBUG)
			ft_printf("%sMAIN: |[%p] - [%s]|%s\n", CLR_RED, buff, buff, CLR_RESET);
		
		if (!ft_strequ(buff, ""))
			cmd_input(buff, g_env);
		// free(bufer);
	}
	return (0);
	(void)argc;
	(void)argv;
}
