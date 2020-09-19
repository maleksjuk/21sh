# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdaemoni <vdaemoni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/09 13:47:22 by pguitar           #+#    #+#              #
#    Updated: 2020/09/19 17:22:32 by vdaemoni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

INC = -I ./includes/

SRCS_NAME = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
			ft_memcpy.c ft_memmove.c ft_memset.c ft_strcat.c ft_strchr.c \
			ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c \
			ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnstr.c ft_strrchr.c \
			ft_strstr.c ft_tolower.c ft_toupper.c ft_putchar.c ft_putstr.c \
			ft_putendl.c ft_putnbr.c ft_itoa.c ft_strsplit.c ft_strtrim.c \
			ft_strjoin.c ft_strsub.c ft_strnequ.c ft_strequ.c ft_strmapi.c \
			ft_strmap.c ft_striteri.c ft_striter.c ft_strclr.c ft_strdel.c \
			ft_strnew.c ft_memdel.c ft_memalloc.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
			ft_lstiter.c ft_lstmap.c ft_min.c ft_max.c ft_isspace.c \
			ft_isupper.c ft_islower.c ft_strnlen.c ft_tabfree.c \
		ft_printf.c format.c pars_1.c pars_2.c size.c ft_c.c \
		ft_d.c ft_u.c ft_o.c ft_x.c ft_p.c ft_s.c color.c \
		ft_x_solver.c conversion.c ft_i.c ft_lib_len.c ft_s_adapt.c \
		ft_d_adapt.c floats_left.c floats_right.c floats_flags.c \
		get_next_line.c ft_strtok.c ft_tablen.c double_to_single.c

SRCS_PATH = srcs/
OBJ_PATH  = obj/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@

clean:
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re