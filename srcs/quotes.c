/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:05:58 by obanshee          #+#    #+#             */
/*   Updated: 2020/09/08 17:25:18 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quote(int *quote, int *quote_rec)
{
	if (quote_rec)
	{
		quote[0] = quote_rec[0];
		quote[1] = quote_rec[1];
	}
	else
	{
		quote[0] = 0;
		quote[1] = 0;
	}
}

char	*get_from_wait_quotes(t_env *env, int quote[2])
{
	char	*bufer;
	char	*continue_cmd;

	if (quote[0])
		ft_printf("\033[31mquote> \033[0m");
	else if (quote[1])
		ft_printf("\033[31mdquote> \033[0m");
	bufer = mega_read(0);
	continue_cmd = check_symbols(env, bufer, quote);
	free(bufer);
	return (continue_cmd);
}

void	check_quote_position(char *cmd, char *str, int *i, int quote[2])
{
	int	flag;

	flag = 0;
	if (cmd[i[0]] == '\'' && quote[1] == 0)
	{
		quote[0] = !quote[0];
		flag = 1;
	}
	else if (cmd[i[0]] == '"' && quote[0] == 0)
	{
		quote[1] = !quote[1];
		flag = 1;
	}
	if (cmd[i[0]] != '~' && cmd[i[0]] != '$' && !flag)
		str[i[1]] = cmd[i[0]];
	if (flag)
		i[1]--;
}

char	*quotes_are_over(t_env *env, char *str, int *quote, int *i)
{
	char	*to_replace;
	char	*new_str;

	if (quote[0] || quote[1])
	{
		str[++i[1]] = '\n';
		to_replace = get_from_wait_quotes(env, quote);
		new_str = ft_strjoin(str, to_replace);
		free(str);
		free(to_replace);
		str = new_str;
	}
	return (str);
}
