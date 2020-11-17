/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:08:48 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/15 19:18:10 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_echo(char *str)
{
	if (str)
		ft_printf("%s", str);
	// else
	// {
	ft_printf("\n");
		// return (0);
	// }

	// // ----------- DELETE --------------
	// ft_printf("%s", CLR_INVERSE);
	// for (int i = 0; i < ft_strlen(str); i++)
	// {
	// 	if (ft_isprint(str[i]))
	// 		ft_printf("%c", str[i]);
	// 	else
	// 		ft_printf("{%d}", (unsigned char)str[i]);
	// }
	// ft_printf("%s\n", CLR_RESET);
	// // ----------- DELETE --------------

	return (0);
}

int		cmd_pwd(char *str)
{
	char	*path;
	char	*tmp;

	tmp = ft_strtrim(str);
	if (ft_strlen(tmp) > 4)
	{
		free(tmp);
		error_message("pwd", "too many arguments");
		return (1);
	}
	free(tmp);
	path = ft_strnew(LEN_PATH);
	path = getcwd(path, LEN_PATH);
	if (!path)
		error_message("getcwd", "error");
	ft_printf("%s\n", path);
	free(path);
	return (0);
}

int		cmd_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s\n", env->str);
		env = env->next;
	}
	return (0);
}

void	cmd_unsetenv(char *key, t_env *env)
{
	t_env	*prev;

	prev = env;
	while (env)
	{
		if (ft_strequ(env->key, key))
		{
			prev->next = env->next;
			free_one_env(env);
			break ;
		}
		prev = env;
		env = env->next;
	}
}
