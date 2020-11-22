/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:57:57 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/22 03:53:10 by obanshee         ###   ########.fr       */
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

void	term_init(void)
{
	extern t_term	*g_term;
	char			*buff;

	if ((getenv("TERM") == NULL) ||
		(buff = ft_strdup(getenv("TERM"))) == NULL)
		error_message("error with environment", "TERM");
	if (tgetent(NULL, buff) <= 0)
		error_message("error with function", "tgetent()");
	g_term = (t_term *)malloc(sizeof(t_term));
	g_term->fd = STDOUT_FILENO;
	tcgetattr(g_term->fd, &g_term->oldt);
	ft_memcpy(&g_term->newt, &g_term->oldt, sizeof(g_term->oldt));
	g_term->newt.c_lflag &= ~(ICANON | ECHO | ECHONL | IEXTEN);
	g_term->newt.c_cc[VMIN] = 1;
	g_term->newt.c_cc[VTIME] = 0;
	if (tcsetattr(g_term->fd, TCSANOW, &g_term->newt) == -1)
		error_message("failed set new attributes", "tcsetattr()");
	ft_putstr_fd(tgetstr("cl", NULL), g_term->fd);
	ft_putstr_fd(tgetstr("ti", NULL), g_term->fd);
	ft_putstr_fd(tgetstr("vs", NULL), g_term->fd);
}

int		main(int argc, char **argv, char **envp)
{
	char	*buff;

	term_init();
	g_env = get_env(envp);
	if (!g_env)
		return (error_message("error", "null env"));
	g_hist = NULL;
	update_lvl();
	ft_printf("%s%s%s* * * 21SH [start] * * *%s\n",
		CLR_BOLD, CLR_GREEN, CLR_INVERSE, CLR_RESET);
	while (21)
	{
		signals();
		print_prompt();
		buff = get_cmd(0);
		if (ft_strequ(buff, "\x04"))
			cmd_exit("exit 0");
		if (!ft_strequ(buff, ""))
			cmd_input(buff, g_env);
	}
	return (0);
	(void)argc;
	(void)argv;
}
