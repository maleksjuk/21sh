/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_to_single.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 17:11:13 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/10/14 13:15:15 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*double_to_single(char **s)
{
	char	*res;
	char	*help;
	int		i;

	i = 0;
	res = ft_strdup(s[i]);
	while (s[++i])
	{
		help = ft_strjoin(res, " ");
		free(res);
		res = ft_strjoin(help, s[i]);
		free(help);
	}
	return (res);
}
