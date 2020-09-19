/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_to_single.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 17:11:13 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/09/19 17:21:28 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*double_to_single(char **s)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup(s[i]);
	while (s[++i])
	{
		res = ft_strjoin(res, " ");
		res = ft_strjoin(res, s[i]);
	}
	return (res);
}
