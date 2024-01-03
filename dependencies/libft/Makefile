# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 17:54:42 by jbadaire          #+#    #+#              #
#    Updated: 2023/01/17 17:54:46 by jbadaire         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

RM					=	rm -rf

CC					=	gcc
FLAGS				=	-Wall -Wextra -Werror
NAME				=	libft.a

BUILD_DIRECTORY		= 	./build/

SRCS			=						\
	chained_utils/ft_lst_new.c		\
	chained_utils/ft_lst_add_front.c	\
	chained_utils/ft_lst_size.c			\
	chained_utils/ft_lst_last.c			\
	chained_utils/ft_lst_add_back.c		\
	chained_utils/ft_lst_delone.c		\
	chained_utils/ft_lst_clear.c		\
	chained_utils/ft_lst_iter.c			\
	char_utils/ft_is_sign.c			\
	char_utils/ft_is_whitespace.c		\
	char_utils/ft_is_space.c			\
	char_utils/ft_is_alpha_num.c		\
	char_utils/ft_is_alpha.c			\
	char_utils/ft_is_ascii.c			\
	char_utils/ft_is_digit.c			\
	char_utils/ft_is_print.c			\
	char_utils/ft_to_lower.c			\
	char_utils/ft_to_upper.c			\
	ft_printf/ft_printf.c			\
	ft_printf/ft_args_handler.c			\
	ft_printf/ft_get_address.c			\
	ft_printf/ft_get_base16.c			\
	ft_printf/ft_get_char.c				\
	ft_printf/ft_get_integer.c			\
	ft_printf/ft_get_string.c			\
	get_next_line/get_next_line.c	\
	get_next_line/get_next_line_utils.c	\
	mem_utils/ft_calloc.c			\
	mem_utils/ft_memset.c				\
	mem_utils/ft_memchr.c				\
	mem_utils/ft_memcmp.c				\
	mem_utils/ft_memcpy.c				\
	mem_utils/ft_memmove.c				\
	put_utils/ft_putchar_fd.c		\
	put_utils/ft_putstr_fd.c			\
	put_utils/ft_putendl_fd.c			\
	put_utils/ft_putnbr_fd.c			\
	string_utils/ft_bzero.c			\
	string_utils/ft_strlen.c			\
	string_utils/ft_strlcat.c			\
	string_utils/ft_strrchr.c			\
	string_utils/ft_strchr.c 			\
	string_utils/ft_strncmp.c			\
	string_utils/ft_strnstr.c			\
	string_utils/ft_strdup.c			\
	string_utils/ft_strlcpy.c			\
	string_utils/ft_substr.c			\
	string_utils/ft_strjoin.c			\
	string_utils/ft_strtrim.c			\
	string_utils/ft_split.c				\
	string_utils/ft_striteri.c			\
	string_utils/ft_strmapi.c			\
	tab_utils/ft_str_tab_len.c		\
	ft_atoi.c						\
	ft_itoa.c							\

OBJS	= $(addprefix $(BUILD_DIRECTORY), $(SRCS:.c=.o))

all:	$(NAME)

so:		$(all)

$(NAME): $(BUILD_DIRECTORY) $(OBJS) .includes/*.h
	ar -rcs $(BUILD_DIRECTORY)$(NAME) $(OBJS)

$(BUILD_DIRECTORY)%.o: %.c Makefile .includes/*.h
	$(CC) $(FLAGS) -I.includes/ -c $< -o $@

$(BUILD_DIRECTORY):
	mkdir -p $(BUILD_DIRECTORY)chained_utils $(BUILD_DIRECTORY)char_utils $(BUILD_DIRECTORY)ft_printf $(BUILD_DIRECTORY)get_next_line $(BUILD_DIRECTORY)mem_utils $(BUILD_DIRECTORY)put_utils $(BUILD_DIRECTORY)string_utils $(BUILD_DIRECTORY)tab_utils

clean:
	$(RM) $(BUILD_DIRECTORY)

fclean:	clean
	$(RM) $(NAME) *.out *.gch *.o .so

re:		fclean $(NAME)

.PHONY:	fclean clean all re
