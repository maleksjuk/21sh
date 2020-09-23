/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:22:44 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/09/23 15:22:30 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_to_pipe(int *pipe_fd, int fd_right)
{
	int		save_fd_out;
	char	buf[BUFF_SIZE];
	ssize_t	result;

	save_fd_out = dup(STDOUT_FILENO);
	close(pipe_fd[0]);
	while ((result = read(fd_right, buf, BUFF_SIZE)) > 0)
		write(pipe_fd[1], buf, (size_t)result);
	close(pipe_fd[1]);
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
	close(fd_right);
	wait(NULL);
}

static void	fork_that(char **cmd, int fd_left, int fd_right)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) < 0)
		error_message("Pipe fail", NULL);
	if ((pid = fork()) < 0)
		error_message("Fork fail", NULL);
	else if (!pid)
		dup_exec(cmd, pipe_fd, fd_left);
	else
		write_to_pipe(pipe_fd, fd_right);
}

void		input_redirect(char **cmd)
{
	do_redirect(cmd, "<", O_RDONLY, fork_that);
}
