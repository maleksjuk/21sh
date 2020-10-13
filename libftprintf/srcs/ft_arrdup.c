/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:06:01 by vdaemoni          #+#    #+#             */
/*   Updated: 2020/10/13 18:08:48 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrdup(char **arr)
{
	char	**cpy;
	size_t	i;

	i = -1;
	while (arr[++i])
		NULL;
	cpy = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (arr[++i])
		cpy[i] = ft_strdup(arr[i]);
	cpy[i] = NULL;
	return (cpy);
}
