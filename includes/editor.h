/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:49:50 by obanshee          #+#    #+#             */
/*   Updated: 2020/11/25 20:20:55 by obanshee         ###   ########.fr       */
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

/*
**	Escape codes
*/
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

/*
**	Termcap codes
*/
# define TERM_RIGHT  "nd"
# define TERM_LEFT   "le"
# define TERM_UP     "up"
# define TERM_DOWN   "do"

# define TERM_CLEAR  "cd"
# define TERM_CARRET "cr"

/*
**	ASCII codes
*/
# define CTRL_A 1
# define CTRL_C 3
# define CTRL_D 4
# define CTRL_E 5
# define ESC 27
# define DEL 127

/*
**	Option codes (cut D, copy V, paste B)
*/
# define OPT_C "\xc3\xa7"
# define OPT_X "\xe2\x89\x88"
# define OPT_D "\xe2\x88\x82"
# define OPT_V "\xe2\x88\x9a"
# define OPT_B "\xe2\x88\xab"

# define MSH_HISTORY ".msh_history"
# define HISTORY_LIMIT 50
# define HIST_BUFF_LEN 256

/*
**	Colors
*/
# define CLR_RESET   "\033[0m"
# define CLR_BOLD    "\033[1m"
# define CLR_INVERSE "\033[7m"

# define CLR_RED     "\033[31m"
# define CLR_GREEN   "\033[32m"
# define CLR_YELLOW  "\033[33m"
# define CLR_BLUE    "\033[34m"
# define CLR_MAGENTA "\033[35m"
# define CLR_CYAN    "\033[36m"

typedef struct			s_reader
{
	struct termios		*oldt;
	struct termios		*newt;
	int					fd;
	int					pos;
	ssize_t				len;
	char				c;
	char				esc[32];
	char				*buff;
	struct winsize		ws;
	int					curs_pos[2];
	int					height;
}						t_reader;

typedef struct			s_history
{
	char				*buff;
	char				*save;
	struct s_history	*next;
	struct s_history	*prev;
	char				count;
}						t_history;

t_history				*g_hist;

/*
**  update.c
*/
void					move_cursor(struct winsize ws, int pos);
void					clear_line(t_reader *rdr);
void					print_buffer_actual(t_reader *rdr);
void					update_buffer(t_reader *rdr);
int						backspace(t_reader *rdr);

/*
**  history.c
*/
t_history				*new_history(t_history *current, t_history *last);
void					check_length_buffer(t_history *hist, ssize_t len);
void					reset_history(t_history *hist);

/*
**  escape_ctrl.c
*/
int						check_escape_ctrl(t_reader *rdr);

/*
**  escape_simple.c
*/
int						check_escape_line(t_reader *rdr, int i);
t_history				*check_escape_history(t_reader *rdr, \
											t_history *current);

/*
**	reader.c
*/
t_reader				*set_reader(int fd, t_history *current);
char					*unset_reader(t_reader *rdr);

/*
**	cut_copy_paste.c
*/
int						cut_copy_paste(t_reader *rdr, t_history *current);

/*
**	home_end.c
*/
int						spec_symbol_home(t_reader *rdr);
int						spec_symbol_end(t_reader *rdr);

void					update_cursor_position(t_reader *rdr);

#endif
