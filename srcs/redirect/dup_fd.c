/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:13:26 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/10/10 14:48:12 by vdaemoni         ###   ########.fr       */
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
	cmd_processing(re, env);
	free(re);
	dup2(save_fd, fd_left);
	close(save_fd);
	fd_left == STDOUT_FILENO ? (void)wait(NULL) : exit(EXIT_SUCCESS);
}
