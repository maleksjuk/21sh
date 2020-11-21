/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:54:56 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/11/11 19:54:30 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*converter_type_out(char *txt)
{
	char *res;
	char *helper;

	res = ft_strdup("echo \"");
	helper = ft_strjoin(res, txt);
	free(res);
	res = ft_strjoin(helper, "\" > .heredoc");
	free(helper);
	return (res);
}

static void	converter_type_in(char **cmd)
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
	cmd_processing("rm -rf .heredoc", g_env);
}

void		here_doc(char **cmd)
{
	char *word;
	char **swap;
	char *text;
	char *out;
	char *help;

	help = ft_strnew(1);
	swap = cmd;
	while (*(++swap) && !(ft_strequ(*swap, "<<")))
		NULL;
	word = ft_strdup(*(swap + 1));
	text = get_txt(word, 1, help);
	out = converter_type_out(text);
	redirection(out);
	free(out);
	converter_type_in(cmd);
	free(text);
	free(word);
}
