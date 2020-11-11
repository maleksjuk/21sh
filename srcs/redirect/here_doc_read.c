/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:52:45 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/11/11 19:54:14 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	iseof_in_line(char *line)
{
	while (*line)
	{
		if (*line == 4)
			return (1);
		++line;
	}
	return (0);
}

static char	*get_cm(int fd, int i, int n, int buf_size)
{
	char	*bufer;
	char	smbl[1];
	char	*overflow;

	bufer = ft_strnew(buf_size);
	while (n > 0)
	{
		n = read(fd, smbl, 1);
		if (n == 0)
		{
			bufer[0] = 4;
			bufer[1] = 0;
			break ;
		}
		if (*smbl == '\n')
			break ;
		bufer[i++] = smbl[0];
		if (i == buf_size)
		{
			buf_size *= 2;
			overflow = ft_strnew(buf_size);
			ft_strncpy(overflow, bufer, i);
			free(bufer);
			bufer = overflow;
		}
	}
	return (bufer);
}

char		*get_txt(char *word, int i)
{
	char	*bufer;
	char	*res;
	char	*help;

	res = ft_strnew(1);
	help = ft_strnew(1);
	while (1)
	{
		ft_printf("\033[31mheredoc> \033[0m");
		bufer = get_cm(0, 0, 1, 1024);
		if (ft_strequ(bufer, word) || iseof_in_line(bufer))
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
