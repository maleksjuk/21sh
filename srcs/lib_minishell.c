/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 09:57:50 by obanshee          #+#    #+#             */
/*   Updated: 2020/08/29 11:10:28 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_array_2(int len)
{
	char	**array;
	int		i;

	if (!(array = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	i = 0;
	while (i < len)
		array[i++] = NULL;
	array[len - 1] = NULL;
	return (array);
}

char	*get_name_or_key(char *str, char stop)
{
	char	*prgm;
	int		len;

	len = 0;
	while (str[len] && (str[len] != ' ' && str[len] != stop))
		len++;
	if (!(prgm = ft_strnew(len)))
		return (NULL);
	ft_strncpy(prgm, str, len);
	return (prgm);
}

char	*value_from_env(t_env *env, char *name)
{
	char	*value;

	value = NULL;
	while (env)
	{
		if (ft_strequ(env->key, name))
		{
			value = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	return (value);
}

char	*ft_strtrim_into(char *cmd)
{
	char	*dst;
	int		mas[2];
	char	*src;
	int		quote;

	src = ft_strtrim(cmd);
	if (!(dst = ft_strnew(ft_strlen(src) + 1)))
		return (NULL);
	mas[0] = 0;
	mas[1] = -1;
	quote = 0;
	while (src[++mas[1]])
	{
		if (src[mas[1]] == '"')
			quote = quote ? 0 : 1;
		if (!quote && (src[mas[1]] == ' ' || src[mas[1]] == '\t'))
		{
			if (!(src[mas[1] - 1] == ' ' || src[mas[1] - 1] == '\t'))
				dst[mas[0]++] = ' ';
		}
		else
			dst[mas[0]++] = src[mas[1]];
	}
	free(src);
	return (dst);
}

char	*get_prgm_path_env(char *prgm, char **path_array)
{
	char		*path;
	int			i;
	char		*tmp;
	struct stat	about;

	path = NULL;
	i = -1;
	while (path_array[++i])
	{
		tmp = ft_strjoin(path_array[i], "/\0");
		path = ft_strjoin(tmp, prgm);
		free(tmp);
		if (!access(path, F_OK))
		{
			stat(path, &about);
			if (!access(path, X_OK) && S_ISREG(about.st_mode))
				break ;
		}
		free(path);
		path = NULL;
	}
	return (path);
}
