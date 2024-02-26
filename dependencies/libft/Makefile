RM					=	rm -rf
CC					=	gcc
FLAGS				=	-Wall -Wextra -Werror -MD -g3
NAME				=	libft.a
BUILD_DIRECTORY		= 	./build/
SRCS				=	$(wildcard chained_utils/*.c char_utils/*.c ft_printf/*.c get_next_line/*.c mem_utils/*.c put_utils/*.c string_utils/*.c tab_utils/*.c *.c)
OBJS				=	$(addprefix $(BUILD_DIRECTORY), $(SRCS:.c=.o))

all:	$(NAME)

$(BUILD_DIRECTORY):
	mkdir -p $(BUILD_DIRECTORY)

$(NAME): $(BUILD_DIRECTORY) $(OBJS)
	@if [ ! -f $(BUILD_DIRECTORY)$(NAME) ] || [ $(shell find . -name "*.c" -newer $(BUILD_DIRECTORY)$(NAME)) ]; then \
		ar -rcs $(BUILD_DIRECTORY)$(NAME) $(OBJS); \
	else \
		echo "Nothing to be done for '$@'"; \
	fi

build/%.o: %.c Makefile
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I.includes/ -c $< -o $@

clean:
	$(RM) $(BUILD_DIRECTORY)

fclean:	clean
	$(RM) $(NAME) *.out *.gch *.o .so

re:		fclean $(NAME)

.PHONY:	fclean clean all re