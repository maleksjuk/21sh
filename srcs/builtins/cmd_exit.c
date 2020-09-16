/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:11:55 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/09/16 21:10:16 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_exit(int code)
{
	ft_free_whole(env);
	ft_printf("exit\n\033[1;7;32m* * * 21SH [exit] * * *\033[0m\n");
	exit(code);
}

static int	ft_isdigit_or_minus(int c)
{
	if ((c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}

void		cmd_exit(char *str, int *exit_flag)
{
	int		n;
	char	**av;
	char	**tmp;

	av = ft_strtok(str, " \t\n\r\a");
	tmp = av;
	n = ft_tablen(av);
	if (n == 1)
	{
		ft_tabfree(av);
		do_exit(ft_atoi(*av));
	}
	else if (n == 2)
	{
		n = 0;
		if ((*av)[n] == '-')
			n++;
		while ((*av)[n] && ft_isdigit((*av)[n]))
			n++;
		if ((*av)[n])
			ft_putendl(ft_isdigit_or_minus(**av) ? \
				"exit: badly formed number" : "exit: wrong syntax");
		else
		{
			ft_tabfree(tmp);
			do_exit(ft_atoi(*av));
		}
	}
	else
		ft_putendl("exit: wrong syntax");
	ft_tabfree(tmp);
	*exit_flag = 0;
}
