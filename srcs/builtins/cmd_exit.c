/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 20:11:55 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/11/15 15:17:53 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_exit(int code)
{
	int r;

	r = 0;
	r = (code >= 0 ? (code % 256) : (256 + (code % 256)));
	if ((r % 256) == 0)
		r = 0;
	ft_free_whole(g_env);
	ft_printf("exit code %d\n\033[1;7;32m* * * 21SH [exit] * * *\033[0m\n", r);
	exit(code);
}

static int	ft_isdigit_or_minus(int c)
{
	if ((c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}

static void	returno(char **av)
{
	int		n;
	char	**tmp;

	n = 0;
	tmp = av;
	av++;
	if ((*av)[n] == '-')
		n++;
	while ((*av)[n] && ft_isdigit((*av)[n]))
		n++;
	if ((*av)[n])
		ft_putendl(ft_isdigit_or_minus(**av) ? \
			"exit: badly formed number" : "exit: wrong syntax");
	else
	{
		n = ft_atoi(*av);
		ft_tabfree(tmp);
		do_exit(n);
	}
	return ;
}

void		free_history()
{
	while (g_hist->prev)
		g_hist = g_hist->prev;
	while (g_hist)
	{
		if (g_hist->prev)
			free(g_hist->prev);
		if (g_hist->buff)
			free(g_hist->buff);
		if (g_hist->save)
			free(g_hist->save);
		if (g_hist->next)
			g_hist = g_hist->next;
		else
		{
			free(g_hist);
			g_hist = NULL;
		}
		
	}
}

void		cmd_exit(char *str)
{
	int		n;
	char	**av;

	free_history();
	av = ft_strtok(str, " \t\n\r\a");
	n = ft_tablen(av);
	if (n == 1)
	{
		ft_tabfree(av);
		do_exit(0);
	}
	else if (n == 2)
		returno(av);
	else
		ft_putendl("exit: wrong syntax");
	ft_tabfree(av);
}
