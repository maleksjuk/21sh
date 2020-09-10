/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 06:09:29 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/09/10 06:32:25 by vdaemoni         ###   ########.fr       */
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
