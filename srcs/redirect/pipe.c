/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 16:46:15 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/10/10 16:29:38 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_here(char **cmd1, char **cmd2)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) < 0)
		error_message("Pipe fail", NULL);
	if ((pid = fork()) < 0)
		error_message("Fork fail", NULL);
	else if (!pid)
		dup_exec(cmd2, pipe_fd, STDIN_FILENO);
	else
		dup_exec(cmd1, pipe_fd, STDOUT_FILENO);
}

void		pipeline(char **cmd)
{
	char **swap;
	char **new_cmd;

	swap = cmd;
	while (*(++swap) && !ft_strequ(*swap, "|"))
		NULL;
	new_cmd = (char **)malloc(sizeof(char *) * (size_t)(swap - cmd + 1));
	swap = new_cmd;
	while (!ft_strequ(*cmd, "|") && (*(swap++) = *(cmd++)))
		NULL;
	*swap = NULL;
	fork_here(new_cmd, ++cmd);
	ft_memdel((void *)&new_cmd);
}
