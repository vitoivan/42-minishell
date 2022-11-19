CC = clang
CFLAGS = -Wall -Wextra -Werror -g -c
LFLAGS = -L./dist -lft -lreadline
NAME = minishell

OBJ_DIR = dist
OBJ_DIRS = $(OBJ_DIR) $(OBJ_DIR)/utils

TARGETS = 	main.c \
			utils/get_line_from_terminal.c \
			utils/free_if_exists.c

SRC = $(addprefix ./src/,$(TARGETS)) 
OBJ = $(addprefix ./$(OBJ_DIR)/,$(TARGETS:.c=.o)) 
LIBFT = $(OBJ_DIR)/libft.a
VALGRIND_FLAGS = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

all: $(NAME) 

test: re 
	@clear
	@./$(NAME)

valgrind: $(NAME)
	@$(VALGRIND_FLAGS) ./$(NAME) 

$(NAME): $(LIBFT) $(OBJ_DIRS) $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

$(LIBFT): $(OBJ_DIRS)
	make -C libs/libft
	cp libs/libft/libft.a $(LIBFT) 

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

dclean: fclean
	make -C libs/libft fclean

clean: 
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean $(NAME)

.PHONY: dclean clean fclean all re run valgrind test