/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:20:06 by obanshee          #+#    #+#             */
/*   Updated: 2020/09/18 18:47:37 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_more(char *cmd, t_env *env)
{
	char	*prgm;
	char	**argv;
	int		i;

	argv = cmd_arguments(cmd);
	prgm = cmd_program(argv[0], value_from_env(env, "PATH"));
	if (prgm)
	{
		cmd_system(prgm, argv, env);
		if (argv)
		{
			i = -1;
			while (argv[++i])
				if (argv[i])
					free(argv[i]);
			free(argv);
		}
	}
	else
	{
		error_message("command not found", argv[0]);
		ft_tabfree(argv);
	}
	free(prgm);
	return (0);
}

char	*get_full_cmd(char *cmd, t_env *env)
{
	char	*str;
	char	*new_str;

	str = ft_strtrim(cmd);
	if (!str)
		return (NULL);
	if (ft_strequ(str, ""))
	{
		free(str);
		return (NULL);
	}
	new_str = ft_strtrim_into(str);
	if (!new_str)
		return (NULL);
	free(str);
	str = check_symbols(env, new_str, NULL);
	free(new_str);
	return (str);
}

int		cmd_processing(char *cmd, t_env *env)
{
	char	*str;
	char	*prgm;

	if (!(str = get_full_cmd(cmd, env)))
		return (0);
	if (!(prgm = get_name_or_key(str, ' ')))
		return (error_message("not get program name", str));
	if (ft_strequ(prgm, "echo"))
		cmd_echo(ft_strlen(str) > 5 ? str + 5 : NULL);
	else if (ft_strequ(prgm, "cd"))
		cmd_cd(env, ft_strlen(str) > 2 ? str + 3 : NULL);
	else if (ft_strequ(prgm, "pwd"))
		cmd_pwd(str);
	else if (ft_strequ(prgm, "env"))
		cmd_env(env);
	else if (ft_strequ(prgm, "setenv"))
		cmd_setenv(str + 7, env);
	else if (ft_strequ(prgm, "unsetenv"))
		cmd_unsetenv(str + 9, env);
	else if (ft_strequ(prgm, "exit"))
		cmd_exit(str);
	else
		cmd_more(str, env);
	double_free(str, prgm);
	return (0);
}
