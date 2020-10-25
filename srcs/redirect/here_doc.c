/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:54:56 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/10/25 20:57:08 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char *converter_type_out(char *txt)
{
	char *res;
	char *helper;

	res = ft_strdup("echo ");
	helper = ft_strjoin(res, txt);
	free(res);
	res = ft_strjoin(helper, " > .heredoc\n");
	free(helper);
	return(res);
}

static void converter_type_in(char **cmd)
{
	int		i;
	char	*re;

	i = 0;
	while (cmd[i] && !(ft_strequ(cmd[i], "<<")))
		i++;
	free(cmd[i + 1]);
	cmd[i + 1] = ft_strdup(".heredoc");
	free(cmd[i]);
	cmd[i] = ft_strdup("<");
	re = double_to_single(cmd);
	redirection(re);
	free(re);
	cmd_processing("rm -rf .heredoc", env);
}

void		here_doc(char **cmd)
{
	char *word;
	char **swap;
	char *text;
	char *out;

	swap = cmd;
	while (*(++swap) && !(ft_strequ(*swap, "<<")))
		NULL;
	word = ft_strdup(*(swap + 1));
	text = get_txt(word, 1);
	out = converter_type_out(text);
	redirection(out);
	free(out);
	converter_type_in(cmd);
	free(text);
	free(word);
}
