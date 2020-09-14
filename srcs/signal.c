/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:48:07 by obanshee          #+#    #+#             */
/*   Updated: 2020/09/11 14:05:06 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pid_t	g_pid;

void	cmd_listener(int sig)
{
	if (sig == SIGINT)
		ft_printf("\n");
}

void	main_listener(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		print_prompt();
	}
}

void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		//move_end(NULL);
		//clean_cursor();
		ft_putchar('\n');
		//if (!g_pid)
			print_prompt();
	}
	/*else if (sig == SIGWINCH)
	{
		ioctl(0, TIOCGWINSZ, get_term_size());
		clear_term(NULL);
	}*/
	else if (sig == SIGINFO)
		print_prompt();
}

void	signals(void)
{
	//ioctl(0, TIOCGWINSZ, get_term_size());
	signal(SIGINT, sig_handle);
	//signal(SIGWINCH, sig_handle);
	signal(SIGINFO, sig_handle);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, main_listener);
}
