/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:55:56 by obanshee          #+#    #+#             */
/*   Updated: 2020/09/10 06:12:22 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_symbols(char *str, char *to_replace, int *i)
{
	char	*new_str;

	new_str = ft_strnew(ft_strlen(str) + ft_strlen(to_replace) + LEN_PATH);
	ft_strcpy(new_str, str);
	ft_strcpy(&new_str[*i], to_replace);
	free(str);
	*i += ft_strlen(to_replace) - 1;
	return (new_str);
}

char	*if_need_replace_in_while(t_env *env, char *cmd, int *i, int *quote)
{
	char	*to_replace;

	to_replace = NULL;
	if (cmd[i[0]] == '~' && !quote[0] && !quote[1] &&
			ft_isspace(cmd[i[0] - 1]))
		to_replace = get_tilda(env, &cmd[i[0]]);
	else if (cmd[i[0]] == '$' && !quote[0] && cmd[i[0] + 1] &&
			!ft_isspace(cmd[i[0] + 1]))
		to_replace = get_dollar(env, &cmd[i[0]]);
	else if (cmd[i[0]] == '~' || cmd[i[0]] == '$')
	{
		to_replace = ft_strnew(1);
		to_replace[0] = cmd[i[0]];
	}
	return (to_replace);
}

char	*check_symbols(t_env *env, char *cmd, int quote_rec[2])
{
	char	*str;
	int		i[2];
	int		quote[2];
	char	*to_replace;

	init_quote(quote, quote_rec);
	str = ft_strnew(LEN_PATH);
	i[0] = -1;
	i[1] = -1;
	while (cmd && cmd[++i[0]])
	{
		i[1]++;
		check_quote_position(cmd, str, i, quote);
		to_replace = if_need_replace_in_while(env, cmd, i, quote);
		if (to_replace)
		{
			str = replace_symbols(str, to_replace, &i[1]);
			free(to_replace);
			while (cmd[i[0]] && (ft_isalnum(cmd[i[0]]) || cmd[i[0]] == '~' ||
					cmd[i[0]] == '$' || cmd[i[0]] == '+' || cmd[i[0]] == '-'))
				i[0]++;
			i[0]--;
		}
	}
	return (quotes_are_over(env, str, quote, i));
}
