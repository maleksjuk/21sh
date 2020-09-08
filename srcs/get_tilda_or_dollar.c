/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tilda_or_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 14:53:19 by obanshee          #+#    #+#             */
/*   Updated: 2020/08/30 14:40:20 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*users_tilda(char *str, t_env *env)
{
	int		i;
	char	*user;
	char	*home;

	home = value_from_env(env, "HOME");
	i = ft_strlen(home) - 1;
	while (home[i] && home[i] != '/')
		home[i--] = '\0';
	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			break ;
	user = ft_strjoin_len(home, str, i, ft_strlen(home));
	free(home);
	if (access(user, F_OK))
	{
		error_message("no such file", user);
		free(user);
		return (NULL);
	}
	return (user);
}

char	*get_tilda(t_env *env, char *str)
{
	char	*to_add;
	int		len;

	if (!str)
		return (NULL);
	if (str[1] && str[1] == '+')
		to_add = value_from_env(env, "PWD");
	else if (str[1] && str[1] == '-')
		to_add = value_from_env(env, "OLDPWD");
	else if (!str[1] || str[1] == '/' || str[1] == ' ' || str[1] == ';')
		to_add = value_from_env(env, "HOME");
	else if (str[1] && ft_isalpha(str[1]))
		to_add = users_tilda(&str[1], env);
	else
	{
		len = 0;
		while (str[len] && str[len] != ' ')
			len++;
		to_add = ft_strnew(len);
		ft_strncpy(to_add, str, len);
	}
	if (!to_add)
		return (NULL);
	return (to_add);
}

char	*get_dollar(t_env *env, char *str)
{
	int		len;
	char	*key;
	char	*to_add;

	len = 1;
	while (str[len] && ft_isalnum(str[len]))
		len++;
	key = ft_strnew(len);
	if (!key)
		return (NULL);
	ft_strncpy(key, &str[1], len - 1);
	to_add = value_from_env(env, key);
	free(key);
	if (!to_add)
		return (NULL);
	return (to_add);
}
