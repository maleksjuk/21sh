/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/18 19:57:42 by obanshee         ###   ########.fr       */
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

void	init_term(struct termios *oldt)
{
	struct termios	*newt;

	tcgetattr(STDIN_FILENO, oldt);
	newt = oldt;
	newt->c_lflag &= ~(ICANON | ECHOCTL | ECHO | ISIG);
	newt->c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, newt);
}

struct termios	init_term_2(struct termios *oldt)
{
	struct termios	*newt;

	tcgetattr(STDIN_FILENO, oldt);
	// newt = oldt;
	ft_memcpy(&newt, &oldt, sizeof(oldt));
	newt->c_lflag &= ~(ICANON | ECHOCTL | ECHO | ISIG);
	newt->c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, newt);
	return (*newt);
}

char	*get_cmd(int fd)
{
	// static 
	struct termios oldt;
	// static 
	struct termios tmp;

	struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);


	ft_printf("First state\n1. [%#x]\n", oldt.c_iflag);
		ft_printf("2. [%#x]\n", oldt.c_oflag);
		ft_printf("3. [%#x]\n", oldt.c_cflag);
		ft_printf("4. [%#x]\n", oldt.c_lflag);
	// i = 1;
	// ft_printf("5. ");
	// while (++i < NCCS)
	// 	if (oldt.c_cc[i] != tmp.c_cc[i])
	// 		ft_printf("(%d)[%d / %d] ", i, oldt.c_cc[i], tmp.c_cc[i]);
		ft_printf("6. [%#x]\n", oldt.c_ispeed);
		ft_printf("7. [%#x]\n", oldt.c_ospeed);

	
	// newt = oldt;
	ft_memcpy(&newt, &oldt, sizeof(oldt));
	newt.c_lflag &= ~(ICANON | ECHOCTL | ECHO | ISIG);
	newt.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	// return (*newt);
	tmp = newt;

	// tmp = init_term_2(&oldt);

	char c;
	char esc[32];
	char *buff;
	int pos;
	ssize_t len;
	int i;

	struct winsize ws;
	ioctl(1, TIOCGSIZE, &ws);

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
		{
			buff = "\x04";
			break ;
		}
		else if (c == 3)
		{
			reset_history(current);
			ft_strclr(g_hist->buff);
			buff = g_hist->buff;
			break ;
		}
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
			print_buffer_actual(buff, len, pos, &ws);
		}
		else if (c == ESC)
		{
			i = 1;
			while (!ft_isalpha(esc[i - 1]))
				read(fd, &esc[i++], 1);
			esc[i] = '\0';
			if (ft_strnequ(esc, ESC_HOME, 3))
				c = 1;
			if (ft_strnequ(esc, ESC_END, 3))
				c = 5;
			if (!check_escape_ctrl(esc, buff, &pos, &ws))
				if (!check_escape_line(esc, buff, &pos, &ws))
					current = check_escape_history(esc, buff, &pos, current);
			buff = current->buff;

		}
		else if (ft_isprint(c))
		{
			update_buffer(c, buff, &pos, &len);
			print_buffer_actual(buff, len, pos, &ws);
		}
		if (c == 1)
		{
			i = len / ws.ws_col + 1;
			while (i--)
				check_escape_ctrl(ESC_CTRL_UP, buff, &pos, &ws);
		}
		else if (c == 5)
		{
			i = len / ws.ws_col + 1;
			while (i--)
				check_escape_ctrl(ESC_CTRL_DOWN, buff, &pos, &ws);
		}
		check_length_buffer(current);
		if ((ft_strlen(buff) + 7) % ws.ws_col == 0)
			ft_printf("\n");
		buff = current->buff;
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

	// for (int i = 0; i < ft_strlen(buff); i++)
	// 	if (buff[i] == '\\')
	// 		buff[i] = '\020';

	ft_printf("\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	
	// if (oldt.c_iflag != tmp.c_iflag)
	// 	ft_printf("1. [%d]\n[%d]", oldt.c_iflag, tmp.c_iflag);
	// if (oldt.c_oflag != tmp.c_oflag)
	// 	ft_printf("2. [%d]\n[%d]", oldt.c_oflag, tmp.c_oflag);
	// if (oldt.c_cflag != tmp.c_cflag)
	// 	ft_printf("3. [%d]\n[%d]", oldt.c_cflag, tmp.c_cflag);
	// if (oldt.c_lflag != tmp.c_lflag)
	// 	ft_printf("4. [%#x]\n[%#x]", oldt.c_lflag, tmp.c_lflag);
	// i = 1;
	// ft_printf("5. ");
	// while (++i < NCCS)
	// 	if (oldt.c_cc[i] != tmp.c_cc[i])
	// 		ft_printf("(%d)[%d / %d] ", i, oldt.c_cc[i], tmp.c_cc[i]);
	// if (oldt.c_ispeed != tmp.c_ispeed)
	// 	ft_printf("6. [%d]\n[%d]", oldt.c_ispeed, tmp.c_ispeed);
	// if (oldt.c_ospeed != tmp.c_ospeed)
	// 	ft_printf("7. [%d]\n[%d]", oldt.c_ospeed, tmp.c_ospeed);


	ft_printf("%sTERM%s\n", CLR_MAGENTA, CLR_RESET);
	ft_printf("Return state\n1. [%#x]\n", oldt.c_iflag);
		ft_printf("2. [%#x]\n", oldt.c_oflag);
		ft_printf("3. [%#x]\n", oldt.c_cflag);
		ft_printf("4. [%#x]\n", oldt.c_lflag);
	// i = 1;
	// ft_printf("5. ");
	// while (++i < NCCS)
	// 	if (oldt.c_cc[i] != tmp.c_cc[i])
	// 		ft_printf("(%d)[%d / %d] ", i, oldt.c_cc[i], tmp.c_cc[i]);
		ft_printf("6. [%#x]\n", oldt.c_ispeed);
		ft_printf("7. [%#x]\n", oldt.c_ospeed);
	// if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) == -1)
	// 	ft_printf("[ERROR\a]");
	return (buff);
}


int		main(int argc, char **argv, char **envp)
{
	char	*buff;

	// tputs(tgetstr("se", NULL), 1, ft_myputchar);

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
