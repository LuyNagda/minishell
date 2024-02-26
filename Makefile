# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lunagda <lunagda@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 20:52:05 by luynagda          #+#    #+#              #
#    Updated: 2024/02/26 14:10:42 by lunagda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MAKE_LIBFT = make -C ./dependencies/libft
LIBFT = ./dependencies/libft/build/libft.a

FILES = main.c                         \
    builtins/cd_builtin.c             \
    builtins/echo_builtin.c           \
    builtins/env_builtin.c            \
    builtins/exit_builtin.c           \
    builtins/export_builtin.c         \
    builtins/get_export_values.c      \
    builtins/unset_builtin.c          \
    builtins/pwd_builtin.c            \
    command/command_handler.c         \
    command/command_manager.c         \
    command/command_utils.c           \
    environment/env_getter.c          \
    environment/env_manager.c         \
    environment/env_setter.c          \
    environment/env_transformer.c     \
    exec/exec_dispatcher.c            \
    exec/exec_pipex.c                 \
    exec/path_handler.c               \
    exec/exec_utils.c                 \
    parsing/parsing_utils.c           \
    parsing/on_parsing.c              \
    parsing/post_parsing.c            \
    parsing/pre_parsing.c             \
    parsing/redirection_parsing.c     \
    parsing/redirection_parsing_2.c   \
    parsing/quotes_remover.c          \
    expand/expand_utils.c             \
    expand/expand_utils_2.c           \
    heredoc/heredoc_parsing.c         \
    heredoc/heredoc_parsing_2.c       \
    heredoc/heredoc_utils.c           \
    tokens/tokenizer.c                \
    tokens/tokenizer_utils.c          \
    tokens/tokens_handler.c           \
    tokens/tokens_concat.c            \
    tokens/tokens_utils.c             \
    tokens/tokens_utils_2.c           \
    utils/quote_utils.c               \
    utils/str_utils.c                 \
    utils/str_utils_2.c               \
    utils/messages_utils.c            \
    utils/debug.c                     \
    utils/utils.c                     \
    utils/merge_sort.c                \
    signals/exit_signal.c             \
    signals/heredoc_signal.c          \
    signals/signals_manager.c         

BUILD_DIRECTORY = ./build/

CC = gcc

FLAGS = -c -Wall -Wextra -Werror -g3

OBJS = $(addprefix $(BUILD_DIRECTORY), $(FILES:.c=.o))

$(NAME): $(BUILD_DIRECTORY) $(OBJS) $(LIBFT)
	@NEED_LINK=0; \
	for file in $(OBJS) $(LIBFT); do \
		if [ $$file -nt $(NAME) ]; then \
			NEED_LINK=1; \
			break; \
		fi; \
	done; \
	if [ ! -f $(NAME) ] || [ $$NEED_LINK -eq 1 ]; then \
		$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME); \
	else \
		echo "Nothing to be done for '$@'"; \
	fi

$(LIBFT):
	$(MAKE_LIBFT)

$(BUILD_DIRECTORY)%.o: ./sources/%.c Makefile ./includes/*.h
	$(CC) $(FLAGS) -I ./includes/ -I ./dependencies/libft/.includes/ $< -o $@

$(BUILD_DIRECTORY):
	mkdir -p $(BUILD_DIRECTORY)exec       \
	$(BUILD_DIRECTORY)command             \
	$(BUILD_DIRECTORY)environment         \
	$(BUILD_DIRECTORY)utils               \
	$(BUILD_DIRECTORY)parsing             \
	$(BUILD_DIRECTORY)builtins            \
	$(BUILD_DIRECTORY)tokens              \
	$(BUILD_DIRECTORY)signals             \
	$(BUILD_DIRECTORY)heredoc             \
	$(BUILD_DIRECTORY)expand

all : $(NAME)

clean :
	$(MAKE_LIBFT) clean
	rm -rf $(BUILD_DIRECTORY)

fclean : clean
	$(MAKE_LIBFT) fclean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re minishell
