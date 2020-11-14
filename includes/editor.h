/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:49:50 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/14 19:51:20 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "../libftprintf/includes/ft_printf.h"
# include "../libftprintf/includes/libft.h"
# include "minishell.h"
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define ESC_RIGHT "\033[C"
# define ESC_LEFT  "\033[D"
# define ESC_UP    "\033[A"
# define ESC_DOWN  "\033[B"

# define MSH_HISTORY ".msh_history"
# define HISTORY_LIMIT 50
# define BUFF_LEN 256

# define DEL 127
# define ESC 27

# define DEBUG 1

# define CLR_RESET   "\033[0m"
# define CLR_BOLD    "\033[1m"
# define CLR_INVERSE "\033[7m"

# define CLR_RED     "\033[31m"
# define CLR_GREEN   "\033[32m"
# define CLR_YELLOW  "\033[33m"
# define CLR_BLUE    "\033[34m"
# define CLR_MAGENTA "\033[35m"
# define CLR_CYAN    "\033[36m"


typedef struct 	s_history
{
	char				*buff;
	char				*save;
	struct s_history	*next;
	struct s_history	*prev;
	char				count;
}				t_history;

t_history	*g_hist;

/*
**  update.c
*/
void	clear_line(int pos, int len);
void    print_buffer_actual(char *buff, int len, int pos);
void	update_buffer(char c, char *buff, int *pos, int *len);
void	reset_history(t_history *hist);

/*
**  history.c
*/
t_history	*new_history(t_history *current, t_history *last);
void	check_length_buffer(t_history *hist);

/*
**  ready.c
*/
int		check_escape_line(char *escape, char *buff, int *i);
t_history	*check_escape_history(char *escape, char *buff, int *i, t_history *current);
void	backspace(char *buff, int *pos, int *len);

/*
**  tmp_lib.c
*/
int	    len_tmp(char *str);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*new_str(int len);
int	    get_max(char *buff, char *hist);

#endif
