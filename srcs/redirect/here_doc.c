/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:54:56 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/10/22 12:41:20 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	putstr_fd(char const *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

static char	*get_txt(char *word, int i)
{
	char	*bufer;
	char	*res;
	char	*help;

	res = ft_strnew(1);
	help = ft_strnew(1);
	while (1)
	{
		ft_printf("\033[31mheredoc> \033[0m");
		bufer = get_cmd(0);
		if (ft_strequ(bufer, word))
		{
			free(bufer);
			break ;
		}
		if (i == 0)
			help = ft_strjoin(res, "\n");
		else
			i = 0;
		free(res);
		res = ft_strjoin(help, bufer);
		free(help);
		free(bufer);
	}
	return (res);
}

static void	pognali(int *pipe_fd, char *txt)
{
	int		save_fd_out;

	save_fd_out = dup(STDOUT_FILENO);
	close(pipe_fd[0]);
	putstr_fd(txt, pipe_fd[1]);
	close(pipe_fd[1]);
	dup2(save_fd_out, STDOUT_FILENO);
	close(save_fd_out);
	wait(NULL);
}

static void	fork_here(char **cmd, char *text)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		ft_printf("21sh: Pipe fail\n");
	if ((pid = fork()) < 0)
		ft_printf("21sh: Fork fail\n");
	else if (!pid)
		dup_exec(cmd, pipe_fd, STDIN_FILENO);
	else
		pognali(pipe_fd, text);
}

void		here_doc(char **cmd)
{
	char *word;
	char **swap;
	char *text;

	swap = cmd;
	while (*(++swap) && !(ft_strequ(*swap, "<<")))
		NULL;
	word = ft_strdup(*(swap + 1));
	text = get_txt(word, 1);
	fork_here(cmd, text);
	free(text);
	free(word);
}
