NAME = minishell

MAKE_LIBFT = make -C ./dependencies/libft
LIBFT = ./dependencies/libft/build/libft.a

FILES =	main.c							\
		command/cmd_handler.c			\
		command/cmd_transformer.c		\
		environment/env_getter.c		\
		environment/env_setter.c		\
		environment/env_manager.c		\
		environment/env_transformer.c	\
		tokens/tokens_handler.c			\
		tokens/tokens_concat.c			\
		tokens/tokens_utils.c			\
		parsing/parsing.c				\
		parsing/in_builtins.c			\
		exec/exec_builtin.c				\
		exec/exec_builtin_2.c			\
		exec/exec_pipex.c				\
		exec/exec_extern.c				\
		exec/path_handler.c				\
		exec/exec_utils.c				\
		utils/quote_utils.c				\
		utils/str_utils.c				\
		utils/messages_utils.c			\
		utils/history_utils.c			\
		utils/debug.c					\

BUILD_DIRECTORY = ./build/

CC = gcc

FLAGS = -c -g3

SOURCES = $(addprefix "sources/", $(SRCS:.c=.o))
OBJS = $(addprefix $(BUILD_DIRECTORY), $(FILES:.c=.o))

$(NAME): $(BUILD_DIRECTORY) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT): force
	$(MAKE_LIBFT)

$(BUILD_DIRECTORY)%.o: ./sources/%.c Makefile ./includes/*.h
	$(CC) $(FLAGS) -I ./includes/ $< -o $@

$(BUILD_DIRECTORY):
	mkdir -p $(BUILD_DIRECTORY)exec	\
	$(BUILD_DIRECTORY)command		\
	$(BUILD_DIRECTORY)environment	\
	$(BUILD_DIRECTORY)utils			\
	$(BUILD_DIRECTORY)parsing		\
	$(BUILD_DIRECTORY)tokens

all : $(NAME)

clean :
	$(MAKE_LIBFT) clean
	$(RM) $(NAME)
	rm -rf $(BUILD_DIRECTORY)

fclean : clean
	$(MAKE_LIBFT) fclean
	rm -rf $(NAME)

re : fclean all

force :

.PHONY: all clean fclean re force minishell
