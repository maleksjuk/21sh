/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 11:48:07 by obanshee          #+#    #+#             */
/*   Updated: 2020/09/19 15:31:58 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_listener(int sig)
{
	if (sig == SIGINT)
		ft_printf("\n");
}

void	main_listener(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		print_prompt();
	}
	else if (sig == SIGINFO)
		print_prompt();
}

void	signals(void)
{
	signal(SIGINT, main_listener);
	signal(SIGINFO, main_listener);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
