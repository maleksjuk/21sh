/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:08:59 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/09/24 16:30:07 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_fd(char **cmd, int fd_left, int fd_right)
{
	int		fd_save;
	char	*re;

	re = double_to_single(cmd);
	fd_save = dup(fd_left);
	dup2(fd_right, fd_left);
	cmd_processing(re, env);
	dup2(fd_save, fd_left);
	free(re);
	close(fd_right);
	close(fd_save);
}

void		output_append_redirect(char **cmd)
{
	do_redirect(cmd, ">>", O_WRONLY | O_CREAT | O_APPEND, dup_fd);
}

void		output_redirect(char **cmd)
{
	do_redirect(cmd, ">", O_WRONLY | O_CREAT | O_TRUNC, dup_fd);
}
