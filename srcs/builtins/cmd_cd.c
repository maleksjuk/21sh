/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:40:11 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/09 20:41:45 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*helper_cd(char *path, char *current_path, int *i)
{
	struct stat	about;
	char		*search_path;

	while (current_path[*i])
		(*i)++;
	if (*i >= LEN_PATH)
		return (NULL);
	current_path[*i] = '/';
	if (path[0] != '/')
		search_path = ft_strjoin(current_path, path);
	else
		search_path = ft_strdup(path);
	if (stat(search_path, &about))
		ft_printf("cd: no such file or directory: %s\n", path);
	else if (access(search_path, F_OK))
		ft_printf("cd: no such file or directory: %s\n", path);
	else if (!S_ISDIR(about.st_mode))
		ft_printf("cd: not a directory: %s\n", path);
	else if (access(search_path, X_OK))
		ft_printf("cd: permission denied: %s\n", path);
	else
		*i = 0;
	return (search_path);
}

void	change_one_env(t_env *env, char *value)
{
	char	*new_str;

	free(env->value);
	free(env->str);
	env->value = ft_strdup(value);
	if (!(new_str = ft_strjoin(env->key, "=")))
		if (!(new_str = ft_strjoin(env->key, "=")))
			return ;
	env->str = ft_strjoin(new_str, value);
	free(new_str);
}

void	cd_change_env(t_env *env, char *old_dir)
{
	char	*new_dir;

	new_dir = ft_strnew(LEN_PATH);
	new_dir = getcwd(new_dir, LEN_PATH);
	cmd_setenv("PWD=tmp", env);
	cmd_setenv("OLDPWD=tmp", env);
	while (env)
	{
		if (ft_strequ(env->key, "PWD"))
			change_one_env(env, new_dir);
		else if (ft_strequ(env->key, "OLDPWD"))
			change_one_env(env, old_dir);
		env = env->next;
	}
	free(new_dir);
}

void	cmd_cd(t_env *env, char *path)
{
	char	*current_path;
	char	*search_path;
	int		flag;

	current_path = ft_strnew(LEN_PATH);
	current_path = getcwd(current_path, LEN_PATH);
	flag = 0;
	if (!path)
		search_path = value_from_env(env, "HOME");
	else if (ft_strequ(path, "-"))
	{
		search_path = value_from_env(env, "OLDPWD");
		search_path ? ft_printf("%s\n", search_path) : \
			ft_printf("21sh: cd: OLDPWD not set\n");
	}
	else if (!(search_path = helper_cd(path, current_path, &flag)))
		flag = 1;
	if (!chdir(search_path))
		cd_change_env(env, current_path);
	else if (!flag)
		error_message("error", "cd");
	free(current_path);
	free(search_path);
}
