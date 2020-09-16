/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 06:09:29 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/09/16 20:00:30 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	ft_printf("\033[1;34m---21sh$> \033[0m");
}

int		error_message(char *str, char *file)
{
	ft_printf("21sh: %s: %s\n", str, file);
	return (0);
}

void	update_lvl(void)
{
	char	*shlvl1;
	char	*shlvl2;
	char	*tmp;

	if (!(shlvl1 = value_from_env(env, "SHLVL")))
	{
		cmd_setenv("SHLVL=1", env);
		return ;
	}
	tmp = ft_itoa(ft_atoi(shlvl1) + 1);
	shlvl2 = ft_strjoin("SHLVL=", tmp);
	cmd_setenv(shlvl2, env);
	ft_memdel((void *)&shlvl1);
	ft_memdel((void *)&tmp);
	ft_memdel((void *)&shlvl2);
}
