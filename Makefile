CC = clang
CFLAGS = -Wall -Wextra -Werror -g -c
LFLAGS = -L./dist -lft -lreadline
NAME = minishell

OBJ_DIR = dist
OBJ_DIRS = $(OBJ_DIR) $(OBJ_DIR)/utils $(OBJ_DIR)/interpreter $(OBJ_DIR)/cmd

TARGETS = 	main.c \
			utils/get_line_from_terminal.c \
			utils/free_if_exists.c \
			utils/print_lkd_list.c \
			utils/skip_whitespace.c \
			interpreter/ft_tokenizer.c \
			cmd/cmd_new.c \
			

SRC = $(addprefix ./src/,$(TARGETS)) 
OBJ = $(addprefix ./$(OBJ_DIR)/,$(TARGETS:.c=.o)) 
LIBFT = $(OBJ_DIR)/libft.a
VALGRIND_FLAGS = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

all: $(NAME) 

test: re $(NAME)
	@clear
	@./$(NAME)

valgrind: $(NAME)void	print_lkd_list(t_lkd_lst **list)GS) ./$(NAME) 

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

dtest:
	make -C libs/libft test

clean: 
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean $(NAME)

.PHONY: dclean clean fclean all re run valgrind test
