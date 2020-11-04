# include <stdio.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
// #include "../libftprintf/includes/libft.h"
// #include "../includes/minishell.h"


# define KEY_RIGHT_ "\x1b\x5b\x43\x0\x0\x0"
# define KEY_LEFT_  "\x1b\x5b\x44\x0\x0\x0"
# define KEY_UP_    "\x1b\x5b\x41\x0\x0\x0"
# define KEY_DOWN_  "\x1b\x5b\x42\x0\x0\x0"

# define MSH_HISTORY ".msh_history"
# define HISTORY_LIMIT 50

typedef struct 	s_history
{
	char		*buff;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;


/*
**  ready.c
*/
int		check_escape_line(char *escape, char *buff, int *i);
void	clear_line(int pos, int len);
void    print_buffer_actual(char *buff, int len, int pos);
void	update_buffer(char c, char *buff, int *pos, int *len);
void	update_escape(char c, char *escape);
void	backspace(char *buff, int *pos, int *len);

/*
**  tmp_lib.c
*/
int	    len_tmp(char *str);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*new_str(int len);
int	    get_max(char *buff, char *hist);
