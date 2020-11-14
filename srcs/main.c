/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/14 18:19:08 by obanshee         ###   ########.fr       */
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
	char esc[2];
	char *buff;
	int pos;
	int len;
	int	n;

	t_history	*current;

	if (!g_hist)
		g_hist = new_history(NULL, NULL);
	current = g_hist;
	buff = current->buff;

	pos = 0;
	len = 0;

	n = 1;
	while (read(fd, &c, 1) > 0)
	{
		// n = read(fd, &c, 1);
		if (c == 4)
		{
			if (ft_strlen(buff) != 0)
			{
				n = 1;
				continue ;
			}
			else
				return ("\x04");
		}
		if (c == '\n')
		{
			if (ft_strlen(buff) != 0)
			{
				g_hist = new_history(current, g_hist);

				while (current->prev)
					current = current->prev;
				while (current)
				{
					ft_printf("\n%s####: |[%p] - [%s]|%s", CLR_YELLOW, current->buff, current->buff, CLR_RESET);
					current = current->next;
				}

				buff = g_hist->prev->buff;
				reset_history(current);
			}
			break ;
		}
		else if (c == DEL)
		{
			backspace(buff, &pos, &len);
			
			// ft_printf("%s", KEY_DOWN_);
			// ft_printf("(%2i)", pos);
			// ft_printf("%s", KEY_UP_);
			// for (int j = 0; j < 3; j++)
			// 	ft_printf("%s", KEY_LEFT_);

			print_buffer_actual(buff, len, pos);
		}
		else if (c == ESC)
		{
			n = read(1, esc, 2);
			if (!check_escape_line(esc, buff, &pos))
				current = check_escape_history(esc, buff, &pos, current);
			buff = current->buff;
		}
		else
		{
			update_buffer(c, buff, &pos, &len);
			print_buffer_actual(buff, len, pos);
		}
		check_length_buffer(current);
		if (DEBUG)
			if (c == '\t')
				exit(1);
	}

	write(1, "\n", 1);
	// ft_printf("check\n");
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
		ft_printf("%sMAIN: |[%p] - [%s]|%s\n", CLR_RED, buff, buff, CLR_RESET);
		
		if (!ft_strequ(buff, ""))
			cmd_input(buff, g_env);
		// free(bufer);
	}
	return (0);
	(void)argc;
	(void)argv;
}
