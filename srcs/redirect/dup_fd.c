/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:13:26 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/10/15 13:59:00 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		dup_exec(char **cmd, int *pipe_fd, int fd_left)
{
	int			save_fd;
	char		*re;

	re = double_to_single(cmd);
	save_fd = dup(fd_left);
	close(pipe_fd[fd_left == STDOUT_FILENO ? 0 : 1]);
	dup2(pipe_fd[fd_left == STDOUT_FILENO ? 1 : 0], fd_left);
	close(pipe_fd[fd_left == STDOUT_FILENO ? 1 : 0]);
	if (!redirection(re))
		cmd_processing(re, env);
	free(re);
	dup2(save_fd, fd_left);
	close(save_fd);
	fd_left == STDOUT_FILENO ? (void)wait(NULL) : exit(EXIT_SUCCESS);
}

static void	dup_plus(char **cmd, int fd_left, int fd_right)
{
	int		fd_save;
	char	*re;

	re = double_to_single(cmd);
	fd_save = dup(fd_left);
	fd_right == -42 ? close(fd_left) : dup2(fd_right, fd_left);
	if (!redirection(re))
		cmd_processing(re, env);
	free(re);
	dup2(fd_save, fd_left);
	close(fd_save);
}

static void	dup_here(char **cmd, int def_fd)
{
	char	**swap;
	int		fd_left;
	int		fd_right;

	fd_left = -1;
	fd_right = -1;
	swap = cmd;
	while (*swap && !is_re(*swap))
		swap++;
	if (*swap)
	{
		if ((fd_left = get_fd(*swap)) == -1)
			fd_left = def_fd;
		ft_arrdelone(cmd, *swap);
		fd_right = get_fd(*swap);
		if (fd_right == -1 && !ft_strcmp(*swap, "-") && fd_left != -1)
			fd_right = -42;
		ft_arrdelone(cmd, *swap);
	}
	if (fd_left != -1 && fd_right != -1 && fd_left != fd_right)
		dup_plus(cmd, fd_left, fd_right);
	else
		ft_printf("%s: Bad file descriptor\n", *cmd);
	ft_tabfree(cmd);
}

void		dup_input(char **cmd)
{
	dup_here(ft_arrdup(cmd), STDIN_FILENO);
}

void		dup_output(char **cmd)
{
	dup_here(ft_arrdup(cmd), STDOUT_FILENO);
}
