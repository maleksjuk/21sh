# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/24 18:49:21 by obanshee          #+#    #+#              #
#    Updated: 2020/11/14 21:12:00 by obanshee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

FLAGS = -g3 #-Wall -Wextra -Werror

LIBFTPRINTF_PATH = libftprintf/
LIBFTPRINTF = libftprintf/libftprintf.a

INC = -I includes/ -I libftprintf/includes/

SRCS_NAME = builtins/cmd_base.c builtins/cmd_cd.c builtins/cmd_setenv.c \
	builtins/cmd_exit.c \
	cmd_system.c env.c lib_minishell.c main.c processing.c \
	signal.c get_tilda_or_dollar.c check_symbols.c quotes.c helpers.c \
	redirect/redirection.c redirect/pipe.c redirect/dup_fd.c redirect/here_doc.c redirect/here_doc_read.c \
	redirect/input_redirect.c redirect/output_redirect.c redirect/main_redirect.c \
	editor/history.c editor/update.c

SRCS_PATH = srcs/
OBJ_PATH  = obj/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFTPRINTF_PATH)
	@gcc -o $(NAME) $(FLAGS) $(INC) $(OBJ) $(LIBFTPRINTF)
	@echo "\033[32mBinary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p obj
	@mkdir -p obj/builtins
	@mkdir -p obj/redirect
	@mkdir -p obj/editor
	@gcc -c $(FLAGS) $(INC) $< -o $@
	@echo "\033[34m\033[1mCompilation of \033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

clean:
	@make -C $(LIBFTPRINTF_PATH)/ clean
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\033[31mObjects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@make -C $(LIBFTPRINTF_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	@echo "\033[31mBinary \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
