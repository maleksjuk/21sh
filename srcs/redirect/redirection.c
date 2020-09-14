/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:42:33 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/09/14 16:45:53 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_re(char *s)
{
	char *result;

	if (s && ((result = ft_strchr(s, R_OUTPUT)) || \
				(result = ft_strchr(s, R_OUTPUT_APPEND)) || \
				(result = ft_strchr(s, R_DUP_OUTPUT)) || \
				(result = ft_strchr(s, R_INPUT)) || \
				(result = ft_strchr(s, R_HERE_DOC)) || \
				(result = ft_strchr(s, R_DUP_INPUT)) || \
				(result = ft_strchr(s, R_PIPELINE))))
		return (*result);
	return (0);
}

static int	got_pipe(char **cmd)
{
	int got_dup;

	got_dup = 0;
	while (*cmd)
	{
		if (ft_strchr(*cmd, R_PIPELINE))
		{
			if (got_dup)
				return (1);
		}
		else if ((ft_strchr(*cmd, R_DUP_INPUT) \
				|| ft_strchr(*cmd, R_DUP_OUTPUT)))
			got_dup = 1;
		else if (is_re(*cmd))
			return (0);
		cmd++;
	}
	return (0);
}

static int	got_re(char **cmd)
{
	int result;

	if (is_re(*cmd))
	{
		ft_printf("21sh: Invalid null command\n");
		return (-1);
	}
	if (got_pipe(cmd))
		return (R_PIPELINE);
	while (*(++cmd))
		if ((result = is_re(*cmd)))
		{
			if (!*(cmd + 1))
			{
				ft_printf("21sh: Missing name for redirect");
				return (-1);
			}
			else if (is_re(*(cmd + 1)))
			{
				ft_printf("21sh: Syntax error");
				return (-1);
			}
			return (result);
		}
	return (0);
}

int			redirection(char *cmd)
{
	char	**cpy;
	int		re;
	void	(*const f[])(char **) = {
			//output_redirect,
			//output_append_redirect,
			//input_redirect,
			pipeline,
			//here_doc,
			//dup_input,
			//dup_output
	};

	cpy = ft_strtok(cmd, " \t\n\r\a");
	if ((re = got_re(cpy)))
	{
		if (re != -1)
			f[re - R_OUTPUT](cpy);
		ft_tabfree(cpy);
		return (1);
	}
	ft_tabfree(cpy);
	return (0);
}
