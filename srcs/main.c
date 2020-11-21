/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/21 12:58:13 by obanshee         ###   ########.fr       */
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

t_reader	*set_reader()
{
	t_reader	*rdr;

	rdr = (t_reader *)malloc(sizeof(t_reader));
	rdr->oldt = (struct termios *)malloc(sizeof(struct termios));
	rdr->newt = (struct termios *)malloc(sizeof(struct termios));
	tcgetattr(STDIN_FILENO, rdr->oldt);
	ft_printf("%sFirst state [%#x]", CLR_MAGENTA, rdr->oldt->c_lflag);
	*(rdr->newt) = *(rdr->oldt);
	rdr->newt->c_lflag &= ~(ICANON | ECHOCTL | ECHO | ISIG);
	rdr->newt->c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, rdr->newt);
	ft_printf("->[%#x]%s\n", rdr->newt->c_lflag, CLR_RESET);
	ioctl(1, TIOCGSIZE, &rdr->ws);
	rdr->pos = 0;
	rdr->len = 0;
	rdr->esc[0] = ESC;
	return (rdr);
}

char	*unset_reader(t_reader *rdr)
{
	char	*buff;

	buff = rdr->buff;
	rdr->oldt->c_lflag &= 0x200005cb;
	tcsetattr(STDIN_FILENO, TCSANOW, rdr->oldt);
	ft_printf("%sReturn state [%#x]%s\n", CLR_MAGENTA, rdr->oldt->c_lflag, CLR_RESET);
	free(rdr->oldt);
	free(rdr->newt);
	free(rdr);
	return (buff);
}

t_history	*check_escape_main(t_reader *rdr, t_history *current)
{
	int	i;

	i = 1;
	while (!ft_isalpha(rdr->esc[i - 1]))
		read(rdr->fd, &rdr->esc[i++], 1);
	rdr->esc[i] = '\0';
	if (ft_strnequ(rdr->esc, ESC_HOME, 3))
		rdr->c = CTRL_A;
	if (ft_strnequ(rdr->esc, ESC_END, 3))
		rdr->c = CTRL_E;
	if (!check_escape_ctrl(rdr))
		if (!check_escape_line(rdr))
			current = check_escape_history(rdr, current);
	rdr->buff = current->buff;
	return (current);
}

int		spec_symbol(t_reader *rdr, t_history *current)
{
	int	i;

	i = 1;
	if (rdr->c == CTRL_D && ft_strlen(rdr->buff) == 0)
		rdr->buff = "\x04";
	else if (rdr->c == CTRL_C)
	{
		reset_history(current);
		ft_strclr(g_hist->buff);
		rdr->buff = g_hist->buff;
	}
	else if (rdr->c == CTRL_A || rdr->c == CTRL_E)
	{
		ft_strcpy(rdr->esc, rdr->c == CTRL_A ? ESC_CTRL_UP : ESC_CTRL_DOWN);
		i = rdr->len / rdr->ws.ws_col + 1;
		while (i--)
			check_escape_ctrl(rdr);
	}
	else if (rdr->c == DEL)
	{
		backspace(rdr);
		print_buffer_actual(rdr);
		i = 0;
	}
	else
		i = 0;
	return (i);
}

char	*get_cmd(int fd)
{
	int i;
	t_history	*current;
	t_reader	*rdr;

	rdr = set_reader();
	rdr->fd = fd;

	if (!g_hist)
		g_hist = new_history(NULL, NULL);
	current = g_hist;
	rdr->buff = current->buff;

	while (read(rdr->fd, &rdr->c, 1) > 0)
	{
		if (rdr->c == '\n')
		{
			if (ft_strlen(rdr->buff) != 0)
			{
				g_hist = new_history(current, g_hist);
				rdr->buff = g_hist->prev->buff;
				reset_history(current);
			}
			break ;
		}
		// else if (rdr->c == DEL)
		// {
		// 	backspace(rdr);
		// 	print_buffer_actual(rdr);
		// }
		else if (rdr->c == ESC)
			current = check_escape_main(rdr, current);
		else if (ft_isprint(rdr->c))
		{
			update_buffer(rdr);
			print_buffer_actual(rdr);
		}
		if (spec_symbol(rdr, current) > 0)
			break ;
		check_length_buffer(current);
		if ((ft_strlen(rdr->buff) + 7) % rdr->ws.ws_col == 0)
			ft_printf("\n");
		rdr->buff = current->buff;
	}

	// if (DEBUG)
	// {
	// 	while (current->prev)
	// 		current = current->prev;
	// 	while (current->next)
	// 	{
	// 		ft_printf("\n%sHIST: |[%p] - b[%s] - s[%s]|%s", CLR_YELLOW, current->buff, current->buff, current->save, CLR_RESET);
	// 		current = current->next;
	// 	}
	// }

	ft_printf("\n");
	return (unset_reader(rdr));
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
