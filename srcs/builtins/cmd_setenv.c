/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:58:38 by obanshee          #+#    #+#             */
/*   Updated: 2020/09/08 17:24:52 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_input_setenv(char *str)
{
	int		space;
	int		equal;
	int		quote;
	int		i;

	i = -1;
	quote = 0;
	space = 0;
	equal = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			quote = quote ? 0 : 1;
		if (!quote && str[i] == ' ')
			space++;
		if (!quote && str[i] == '=')
			equal++;
	}
	if (!equal)
		return (!error_message("setenv", "error numbers of arguments"));
	return (0);
}

void	check_flag_setenv(int flag, char *str, t_env *env)
{
	t_env	*env_new;

	if (!flag)
	{
		if ((env_new = create_one_env(str)))
			env->next = env_new;
	}
}

void	cmd_setenv(char *str, t_env *env)
{
	char	*key;
	int		flag;

	if (!env || check_input_setenv(str))
		return ;
	key = get_name_or_key(str, '=');
	flag = 0;
	while (env)
	{
		if (ft_strequ(env->key, key))
		{
			free(env->str);
			env->str = ft_strdup(str);
			free(env->value);
			env->value = ft_strdup(str + ft_strlen(key) + 1);
			flag = 1;
			break ;
		}
		if (!(env->next))
			break ;
		env = env->next;
	}
	free(key);
	check_flag_setenv(flag, str, env);
}
