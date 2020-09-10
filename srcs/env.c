/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 14:28:32 by obanshee          #+#    #+#             */
/*   Updated: 2020/09/08 17:24:59 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_env_array(t_env *env)
{
	char	**envp;
	t_env	*current;
	int		len;

	current = env;
	len = 0;
	while (current)
	{
		current = current->next;
		len++;
	}
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	len = 0;
	while (env)
	{
		envp[len++] = ft_strdup(env->str);
		env = env->next;
	}
	envp[len] = NULL;
	return (envp);
}

void	delete_env_array(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}

t_env	*free_one_env(t_env *one)
{
	if (one->key)
		free(one->key);
	if (one->value)
		free(one->value);
	if (one->str)
		free(one->str);
	free(one);
	return (NULL);
}

t_env	*create_one_env(char *str)
{
	t_env	*one;
	int		i;

	if (!(one = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	one->str = ft_strdup(str);
	i = 0;
	while (str[i] != '=')
		i++;
	one->key = ft_strnew(i);
	one->key = ft_strncpy(one->key, str, i);
	one->value = ft_strdup(&(str[i + 1]));
	one->next = NULL;
	if (!(one->key && one->value && one->str))
		return (free_one_env(one));
	return (one);
}

t_env	*get_env(char **envp)
{
	t_env	*env_begin;
	t_env	*env_prev;
	t_env	*env_curr;
	int		len;

	if (!envp || !envp[0])
		return (NULL);
	env_begin = create_one_env(envp[0]);
	env_prev = env_begin;
	len = 0;
	while (envp[++len])
	{
		env_curr = create_one_env(envp[len]);
		env_prev->next = env_curr;
		env_prev = env_curr;
	}
	return (env_begin);
}
