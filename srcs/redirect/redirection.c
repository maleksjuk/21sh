/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:42:33 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/11/08 23:14:11 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_re(char *s)
{
	int	result;

	result = 0;
	if (s)
	{
		if (ft_strequ(s, "|"))
			result = 1;
		if (ft_strequ(s, ">"))
			result = 2;
		if (ft_strequ(s, ">>"))
			result = 3;
		if (ft_strequ(s, "<"))
			result = 4;
		if (ft_strstr(s, "<&"))
			result = 5;
		if (ft_strstr(s, ">&"))
			result = 6;
		if (ft_strequ(s, "<<"))
			result = 7;
	}
	return (result);
}

static int	pipe_after_dup(char **cmd)
{
	int got_dup;

	got_dup = 0;
	while (*cmd)
	{
		if (ft_strequ(*cmd, "|"))
		{
			if (got_dup)
				return (1);
		}
		else if ((ft_strstr(*cmd, "<&") \
				|| ft_strstr(*cmd, ">&")))
			got_dup = 1;
		else if (is_re(*cmd))
			return (0);
		cmd++;
	}
	return (0);
}

static int	get_index(char **cmd)
{
	int result;

	if (is_re(*cmd))
	{
		ft_printf("21sh: Invalid null command\n");
		return (-1);
	}
	if (pipe_after_dup(cmd))
		return (1);
	while (*(++cmd))
		if ((result = is_re(*cmd)))
		{
			if (!*(cmd + 1))
			{
				ft_printf("21sh: Missing name for redirect\n");
				return (-1);
			}
			else if (is_re(*(cmd + 1)))
			{
				ft_printf("21sh: Syntax error\n");
				return (-1);
			}
			return (result);
		}
	return (0);
}

static char	*for_dup(char *arr)
{
	char	*cpy;
	size_t	i;

	i = -1;
	cpy = ft_strnew(ft_strlen(arr) + 1);
	while (arr[++i])
	{
		if (arr[i] == '&')
		{
			if (arr[i - 1] == '>' || arr[i - 1] == '<')
			{
				ft_strncat(cpy, arr, i + 1);
				ft_strcat(cpy, " ");
				ft_strcat(cpy, &arr[i + 1]);
				break ;
			}
		}
	}
	return (cpy);
}

int			redirection(char *cmd)
{
	char	**cpy;
	char	*duper;
	int		index;
	void	(*const f[])(char **) = {
			pipeline, output_redirect, output_append_redirect,
			input_redirect, dup_input, dup_output, here_doc
	};

	index = is_re(cmd);
	duper = NULL;
	if (index == 6 || index == 5)
		duper = for_dup(cmd);
	cpy = (duper ? hypertok(duper) : hypertok(cmd));
	duper ? free(duper) : NULL;
	if ((index = get_index(cpy)))
	{
		if (index != -1)
			f[index - 1](cpy);
		ft_tabfree(cpy);
		return (1);
	}
	ft_tabfree(cpy);
	return (0);
}
