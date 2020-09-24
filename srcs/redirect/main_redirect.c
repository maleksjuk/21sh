/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 15:06:36 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/09/24 16:19:02 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_fd(char *s)
{
	int		fd;

	if (!s)
		return (-1);
	while (*s && !ft_isdigit(*s) && *s != '-')
		s++;
	if (!*s)
		return (-1);
	fd = ft_atoi(s);
	return (fcntl(fd, F_GETFD) ? -1 : fd);
}

int		do_redirect(char **cmd, char *sym, int o_flag, \
					void (*main_maker)(char **, int, int))
{
	int		fd_left;
	int		fd_right;
	char	**swap;
	char	*tmp;

	swap = cmd;
	while (*(++swap) && !(tmp = ft_strstr(*swap, sym)))
		NULL;
	if (*swap == tmp || (fd_left = get_fd(*swap)) == -1)
	{
		fd_left = (ft_strequ(sym, "<") ? STDIN_FILENO : STDOUT_FILENO);
		*tmp = 0;
	}
	if ((fd_right = open(*(++swap), o_flag, 0664)) == -1)
		return (error_message("Problem with file", *swap));
	if (*tmp || tmp == *(swap - 1))
	{
		tmp = *swap;
		ft_arrdelone(cmd, *(swap - 1));
		ft_arrdelone(cmd, tmp);
	}
	else
		ft_arrdelone(cmd, *swap);
	main_maker(cmd, fd_left, fd_right);
	return (0);
}
