/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hypertok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 23:04:53 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/11/09 18:05:25 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	if (c == ' ' || c == '\t' || c == '\a' || c == '\r')
		return (3);
	return (0);
}

static int	ft_hm(char *s)
{
	int i;
	int res;

	res = 0;
	i = -1;
	while (s[++i])
	{
		if (is_sep(s[i]))
		{
			if (is_sep(s[i]) == 1)
			{
				res++;
				while (s[++i] && is_sep(s[i]) != 1)
					NULL;
			}
			else if (is_sep(s[i]) == 2)
			{
				res++;
				while (s[++i] && is_sep(s[i]) != 2)
					NULL;
			}
		}
		else
		{
			while (s[i] && !is_sep(s[i]))
				i++;
			res++;
			i--;
		}
	}
	return (res);
}

static int	before_len(char *s, int sep)
{
	int i;

	i = 0;
	if (sep == 3)
	{
		while (s[i] && !is_sep(s[i]))
			i++;
		return (i);
	}
	else
	{
		s++;
		while (s[i] && is_sep(s[i]) != sep)
			i++;
		return (i + 2);
	}
}

static void	cycle(char *cmd, int words, int i, char **tok)
{
	int j;
	int n;

	n = 0;
	j = -1;
	while (++i < words)
	{
		while (is_sep(*cmd) == 3)
			cmd++;
		n = is_sep(*cmd);
		if (n > 0)
		{
			j = before_len(cmd, n);
			tok[i] = ft_strsub(cmd, 1, j - 2);
			while (j--)
				cmd++;
		}
		else
		{
			j = before_len(cmd, 3);
			tok[i] = ft_strsub(cmd, 0, j);
			while (j--)
				cmd++;
		}
	}
}

char		**hypertok(char *cmd)
{
	int		i;
	int		words;
	char	**tok;

	i = -1;
	words = ft_hm(cmd);
	tok = (char **)malloc(sizeof(char *) * (words + 1));
	cycle(cmd, words, i, tok);
	tok[words] = NULL;
	return (tok);
}
