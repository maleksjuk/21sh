/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:49:50 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/18 19:17:08 by obanshee         ###   ########.fr       */
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

# define ESC_CTRL_RIGHT "\033[1;5C"
# define ESC_CTRL_LEFT  "\033[1;5D"
# define ESC_CTRL_UP    "\033[1;5A"
# define ESC_CTRL_DOWN  "\033[1;5B"

# define ESC_HOME "\033[H"
# define ESC_END  "\033[F"

// # define ESC_CTRL_UP    "\033[[A"
// # define ESC_CTRL_DOWN  "\033[[B"

# define K_CTRL_U		"\x15\x0\x0\x0\x0\x0"

// # define K_CTRL_UP		"\x1b\x5b\x31\x3b\x35\x41"

// # define K_CTRL_UP		"\x1b\x5b\x38\x3b\x35\x41"
// # define K_CTRL_DOWN		"\x1b\x5b\x38\x3b\x35\x42"
// # define K_CTRL_RIGHT	"\x1b\x5b\x38\x3b\x35\x43"
// # define K_CTRL_LEFT		"\x1b\x5b\x38\x3b\x35\x44"

// # define K_UP			"\x1b\x5b\x41\x0\x0\x0"
// # define K_DOWN			"\x1b\x5b\x42\x0\x0\x0"
// # define K_RIGHT			"\x1b\x5b\x43\x0\x0\x0"
// # define K_LEFT			"\x1b\x5b\x44\x0\x0\x0"

# define MSH_HISTORY ".msh_history"
# define HISTORY_LIMIT 50
# define HIST_BUFF_LEN 256

# define DEL 127
# define ESC 27

# define DEBUG 0

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
void	move_cursor(struct winsize *ws, int pos);
void	clear_line(int pos, ssize_t len, struct winsize *ws);
void    print_buffer_actual(char *buff, ssize_t len, int pos, struct winsize *ws);
void	update_buffer(char c, char *buff, int *pos, ssize_t *len);
void	reset_history(t_history *hist);

/*
**  history.c
*/
t_history	*new_history(t_history *current, t_history *last);
void	check_length_buffer(t_history *hist);

/*
**  ready.c
*/
int		check_escape_ctrl(char *escape, char *buff, int *i, struct winsize *ws);
int		check_escape_line(char *escape, char *buff, int *i, struct winsize *ws);
t_history	*check_escape_history(char *escape, char *buff, int *i, t_history *current);
void	backspace(char *buff, int *pos, ssize_t *len);

void	init_term(struct termios *oldt);
struct termios	init_term_2(struct termios *oldt);

#endif
