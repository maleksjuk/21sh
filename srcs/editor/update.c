/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:57:13 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/14 19:52:07 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	clear_line(int pos, int len)
{
	int	i;

	i = pos;
	ft_printf("%s", ESC_LEFT);
	while (i++ <= len)
		write(1, " ", 1);
	ft_printf("\r");
	print_prompt();
	i = 0;
	while (++i < pos)
		write(1, " ", 1);
}

void    print_buffer_actual(char *buff, int len, int pos)
{
	int	i;

	clear_line(pos, len + 1);
	i = pos - 2;
	while (++i < len && buff[i])
		write(1, &buff[i], 1);
	// ft_printf("%s", &buff[i]);
	ft_printf("\r");
	i = -1;
	print_prompt();
	// ft_printf("%s", buff);
	while (++i < pos)
		write(1, &buff[i], 1);
	// while (--len > pos)
	// 	write(1, KEY_LEFT_, 3);
}

void	update_buffer(char c, char *buff, int *pos, int *len)
{
	int i;

	i = ++(*len);
	while (--i > *pos)
		buff[i] = buff[i - 1];
	buff[(*pos)++] = c;
}

void	backspace(char *buff, int *pos, int *len)
{
	int	i;

	if (*pos == 0)
		return ;
	i = *pos - 1;
	while (++i <= *len)
		buff[i - 1] = buff[i];
	buff[--(*len)] = '\0';
	(*pos)--;
}
