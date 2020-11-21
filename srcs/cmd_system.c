/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_system.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 10:35:13 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/21 09:55:51 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_program(char *prgm, char *path_env)
{
	char		*path;
	char		**path_array;
	struct stat	about;
	int			i;

	if (ft_strchr(prgm, '/'))
		if (!access(prgm, F_OK))
		{
			stat(prgm, &about);
			if (!access(prgm, X_OK) && S_ISREG(about.st_mode))
				return (ft_strdup(prgm));
		}
	if (!path_env)
		return (NULL);
	path_array = ft_strsplit(path_env, ':');
	free(path_env);
	path = get_prgm_path_env(prgm, path_array);
	i = -1;
	while (path_array[++i])
		free(path_array[i]);
	free(path_array);
	if (!path)
		return (NULL);
	return (path);
}

int		nbr_args(char *cmd)
{
	int	len;
	int	quote;

	len = 1;
	quote = 0;
	while (*(cmd + 1))
	{
		if (*cmd == '"')
		{
			if (quote)
				quote = 0;
			else
				quote = 1;
		}
		if (!quote)
			if (*cmd == ' ' && *(cmd + 1) != ' ' && *(cmd + 1) != '\t')
				len++;
		cmd++;
	}
	return (len);
}

char	*one_arg(char *cmd)
{
	char	*word;
	int		i;

	i = 0;
	if (*cmd == '"')
	{
		cmd++;
		while (cmd[i] && cmd[i] != '"')
			i++;
	}
	else
		while (cmd[i] && cmd[i] != ' ')
			i++;
	if (!(word = ft_strnew(i + 1)))
		return (NULL);
	word = ft_strncpy(word, *cmd == '"' ? cmd + 1 : cmd, i);
	return (word);
}

char	**cmd_arguments(char *cmd)
{
	char	**arguments;
	int		len;
	int		i;

	len = nbr_args(cmd);
	if (!(arguments = set_array_2(len + 2)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;
		arguments[i] = one_arg(cmd);
		if (*cmd == '"')
			cmd++;
		cmd += ft_strlen(arguments[i]);
		if (*cmd == '"')
			cmd++;
		i++;
	}
	return (arguments);
}

int		cmd_system(char *prgm, char **argv, t_env *env)
{
	int		status;
	char	**envp;

	g_pid = fork();
	signal(SIGINT, cmd_listener);
	if (g_pid == -1)
	{
		error_message("fork fail", prgm);
		return (-1);
	}
	else if (g_pid == 0)
	{
		envp = create_env_array(env);
		execve(prgm, argv, envp);
		delete_env_array(envp);
		exit(-1);
	}
	if (waitpid(g_pid, &status, 0))
		return (-1);
	else if (WIFEXITED(status))
		return (WIFEXITED(status));
	return (-1);
}
