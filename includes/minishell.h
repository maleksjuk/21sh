/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:53:05 by obanshee          #+#    #+#             */
/*   Updated: 2020/09/19 15:30:11 by vdaemoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libftprintf/includes/ft_printf.h"
# include "../libftprintf/includes/get_next_line.h"
# include "../libftprintf/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>

# define LEN_PATH 1024

typedef struct		s_env
{
	char			*key;
	char			*value;
	char			*str;
	struct s_env	*next;
}					t_env;

enum				e_replacement
{
	S_WORD = -42,
	S_LINE = -41,
	R_OUTPUT = -40,
	R_OUTPUT_APPEND = -39,
	R_INPUT = -38,
	R_PIPELINE = -37,
	R_HERE_DOC = -36,
	R_DUP_INPUT = -35,
	R_DUP_OUTPUT = -34
};

t_env				*env;

/*
**	main.c
*/
char				*get_cmd(int fd);

/*
**	main_functions.c
*/
int					cmd_more(char *cmd, t_env *env);
int					cmd_processing(char *cmd, t_env *env);

/*
**	helpers.c
*/
int					error_message(char *str, char *file);
void				print_prompt(void);
void				update_lvl(void);
void				ft_free_whole(t_env *env);
void				double_free(char *str1, char *str2);

/*
**	lib_minishell.c
*/
char				**set_array_2(int len);
char				*get_name_or_key(char *str, char stop);
char				*value_from_env(t_env *env, char *name);
char				*ft_strtrim_into(char *cmd);
char				*get_prgm_path_env(char *prgm, char **path_array);

/*
**  cmd_base.c
*/
int					cmd_echo(char *str);
int					cmd_pwd(char *str);
int					cmd_env(t_env *env);
void				cmd_unsetenv(char *key, t_env *env);

/*
**  cmd_exit.c
*/
void				cmd_exit(char *str);

/*
**  cmd_setenv.c
*/
void				cmd_setenv(char *str, t_env *env);

/*
**  cmd_cd.c
*/
void				cmd_cd(t_env *env, char *path);

/*
**  cmd_more.c
*/
char				*cmd_program(char *prgm, char *path_env);
char				**cmd_arguments(char *cmd);
int					cmd_system(char *prgm, char **argv, t_env *env);

/*
**  symbols.c
*/
char				*sml_dollar(char *cmd, t_env *env, int nbr);
char				*get_full_cmd(char *cmd, t_env *env);

/*
**  sml_tilda.c
*/
char				*sml_tilda(char *cmd, t_env *env, int nbr);

/*
**  signal.c
*/
void				cmd_listener(int sig);
void				signals(void);

/*
**	env.c
*/
char				**create_env_array(t_env *env);
void				delete_env_array(char **envp);
t_env				*free_one_env(t_env *one);
t_env				*create_one_env(char *str);
t_env				*get_env(char **envp);

/*
**	check_symbols.c
*/
char				*check_symbols(t_env *env, char *cmd, int quote_rec[2]);

/*
**	quotes.c
*/
void				init_quote(int *quote, int *quote_rec);
char				*get_from_wait_quotes(t_env *env, int quote[2]);
void				check_quote_position(char *cmd, char *str,
										int *i, int quote[2]);
char				*quotes_are_over(t_env *env, char *str, int *quote, int *i);

/*
**	get_tilda_or_dollar.c
*/
char				*get_tilda(t_env *env, char *str);
char				*get_dollar(t_env *env, char *str);

/*
**	redirection.c
*/
int					redirection(char *cmd);
int					is_re(char *s);

/*
**	pipe.c
*/
void				pipeline(char **cmd);

/*
**	dup_fd.c
*/
void				dup_exec(char **cmd, int *pipe_fd, int fd_left);

#endif
