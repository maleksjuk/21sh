/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 19:05:28 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/28 11:47:09 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32
# define MAX_FD 10240

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

char	*memory_line(char **str, int fd, char **line);
int		kostyl(int ret, char **str, int fd, char **line);
int		get_next_line(const int fd, char **line);

#endif
