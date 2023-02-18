CC = clang
CFLAGS = -Wall -Wextra -Werror -g -c
LFLAGS = -L./dist -lft -lreadline
NAME = minishell
AR = ar -crs
NAME_LIB = minishell.a


#----------------- directories
OBJ_DIR = dist
OBJ_DIRS = $(OBJ_DIR) \
			$(OBJ_DIR)/utils \
			$(OBJ_DIR)/interpreter \
			$(OBJ_DIR)/cmd \
			$(OBJ_DIR)/builtins \
			$(OBJ_DIR)/pipes \
			$(OBJ_DIR)/tests \
			$(OBJ_DIR)/context 

# -------------- end directories			

# --------------------- source code
TARGETS = 	main.c \
			utils/get_line_from_terminal.c \
			utils/free_if_exists.c \
			utils/debug.c \
			utils/ft_parser_utils.c \
			utils/ft_tokenizer_utils.c \
			interpreter/ft_tokenizer.c \
			interpreter/ft_parser.c \
			utils/print_lkd_list.c \
			utils/skip_whitespace.c \
			utils/print_terminal.c \
			utils/get_hostname.c \
			utils/ft_isspace.c \
			utils/ft_isquote.c \
			utils/skip_quotes.c \
			utils/string_builder.c \
			cmd/cmd_is_valid.c \
			cmd/cmd_try_run.c \
			cmd/path.c \
			cmd/await_cmd_run.c \
			cmd/cmd_exec.c \
			cmd/cmd_get_args.c \
			cmd/cmd_free_args.c \
			cmd/cmd_with_redirect.c \
			cmd/get_cmd_from_line.c \
			pipes/close.c \
			pipes/open.c \
			builtins/utils.c \
			builtins/pwd.c \
			builtins/cd.c \
			builtins/export.c \
			context/init.c \
			context/populate_buffer.c \
			context/update.c \
			context/free.c

SRC = $(addprefix ./src/,$(TARGETS))
SRC_OBJ = $(addprefix ./$(OBJ_DIR)/,$(TARGETS:.c=.o)) 
# --------------------- end source code


# ---------------- tests
TEST_TARGETS =  tests/main.c \
				tests/utils.c \
				tests/first_test.c

TESTS_OBJS = $(addprefix ./$(OBJ_DIR)/,$(TEST_TARGETS:.c=.o))

# -------------------- end tests
			
 
LIBFT = $(OBJ_DIR)/libft.a


VALGRIND_FLAGS = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(NAME) 

test: $(NAME_LIB) $(TESTS_OBJS)
	@clear
	@$(CC) $(TESTS_OBJS) $(LFLAGS) -o $(NAME)_test
	@./$(NAME)_test
	@rm -f $(NAME)_test $(NAME_LIB)


test-valgrind: $(NAME_LIB) $(TESTS_OBJS)
	@clear
	@$(CC) $(TESTS_OBJS) $(LFLAGS) -o $(NAME)_test
	@valgrind $(VALGRIND_FLAGS) ./$(NAME)_test
	@rm -f $(NAME)_test $(NAME_LIB)

$(OBJ_DIR)/tests/%.o: tests/%.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME_LIB): $(LIBFT) $(OBJ) 
	$(AR) $(NAME_LIB) $(LIBFT) $(OBJ)

valgrind: $(NAME)	
	valgrind $(VALGRIND_FLAGS) ./$(NAME) 

$(NAME): $(LIBFT) $(OBJ_DIRS) $(SRC_OBJ)
	$(CC) $(SRC_OBJ) $(LFLAGS) -o $(NAME)

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
	rm -f $(SRC_OBJ)
	rm -f $(TESTS_OBJS)

fclean: clean 
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(NAME_LIB)

re: fclean $(NAME)

.PHONY: dclean clean fclean all re run valgrind test test-valgrind 
