# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 15:40:47 by lunagda           #+#    #+#              #
#    Updated: 2024/02/26 15:54:27 by lunagda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM					=	rm -rf
CC					=	gcc
FLAGS				=	-Wall -Wextra -Werror -MD -g3
NAME				=	libft.a
BUILD_DIRECTORY		= 	./build/
SRCS			=						\
	chained_utils/ft_lst_new		\
	chained_utils/ft_lst_add_front	\
	chained_utils/ft_lst_size			\
	chained_utils/ft_lst_last			\
	chained_utils/ft_lst_add_back		\
	chained_utils/ft_lst_delone		\
	chained_utils/ft_lst_clear		\
	chained_utils/ft_lst_iter			\
	char_utils/ft_is_sign			\
	char_utils/ft_is_whitespace		\
	char_utils/ft_is_space			\
	char_utils/ft_is_alpha_num		\
	char_utils/ft_is_alpha			\
	char_utils/ft_is_ascii			\
	char_utils/ft_is_digit			\
	char_utils/ft_is_print			\
	char_utils/ft_to_lower			\
	char_utils/ft_to_upper			\
	ft_printf/ft_printf			\
	ft_printf/ft_args_handler			\
	ft_printf/ft_get_address			\
	ft_printf/ft_get_base16			\
	ft_printf/ft_get_char				\
	ft_printf/ft_get_integer			\
	ft_printf/ft_get_string			\
	get_next_line/get_next_line	\
	get_next_line/get_next_line_utils	\
	mem_utils/ft_calloc			\
	mem_utils/ft_memset				\
	mem_utils/ft_memchr				\
	mem_utils/ft_memcmp				\
	mem_utils/ft_memcpy				\
	mem_utils/ft_memmove				\
	put_utils/ft_putchar_fd		\
	put_utils/ft_putstr_fd			\
	put_utils/ft_putendl_fd			\
	put_utils/ft_putnbr_fd			\
	string_utils/ft_bzero			\
	string_utils/ft_strlen			\
	string_utils/ft_strlcat			\
	string_utils/ft_strrchr			\
	string_utils/ft_strchr 			\
	string_utils/ft_strncmp			\
	string_utils/ft_strnstr			\
	string_utils/ft_strdup			\
	string_utils/ft_strlcpy			\
	string_utils/ft_substr			\
	string_utils/ft_strjoin			\
	string_utils/ft_strtrim			\
	string_utils/ft_split				\
	string_utils/ft_striteri			\
	string_utils/ft_strmapi			\
	tab_utils/ft_str_tab_len		\
	ft_atoi						\
	ft_itoa							
	
OBJS = $(addsuffix .o, $(addprefix $(BUILD_DIRECTORY), $(SRCS)))
DPDS = $(addsuffix .d, $(addprefix $(BUILD_DIRECTORY), $(SRCS)))

$(BUILD_DIRECTORY)$(NAME): $(OBJS)
	mkdir -p $(dir $(NAME))
	ar rcs $@ $(OBJS)

$(NAME): $(BUILD_DIRECTORY)$(NAME)
	cp $< $@

all:	$(NAME)

build/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I.includes/ -c $< -o $@

clean:
	$(RM) $(BUILD_DIRECTORY)

fclean:	clean
	$(RM) $(NAME) *.out *.gch *.o .so

re:		fclean $(NAME)

.PHONY:	fclean clean all re

-include $(OBJS:.o=.d)