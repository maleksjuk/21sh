/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 16:46:15 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/09/14 17:03:58 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_here(char **cmd1, char **cmd2)
{
	int pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		error_message()
}

void		pipeline(char **cmd)
{
	char **swap;
	char **new_cmd;

	swap = cmd;
	while (*(++swap) && !ft_strchr(*swap, R_PIPELINE))
		NULL;
	new_cmd = (char **)malloc(sizeof(char *) * (size_t)(swap - cmd + 1));
	swap = new_cmd;
	while (!ft_strchr(*cmd, R_PIPELINE) && (*(swap++) = *(cmd++)))
		NULL;
	*swap = NULL;
	fork_here(new_cmd, ++cmd);
	ft_tabfree(new_cmd);
}
