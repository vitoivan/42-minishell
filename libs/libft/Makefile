SRC = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_strcmp.c get_next_line.c

PRINTF = ft_printf/ft_helpers.c ft_printf/ft_itohex.c ft_printf/ft_print_arg.c ft_printf/ft_print_char.c  ft_printf/ft_print_conversion.c ft_printf/ft_print_hex.c ft_printf/ft_print_ptr.c ft_printf/ft_print_signed_digit.c ft_printf/ft_print_str.c ft_printf/ft_print_udigit.c ft_printf/ft_printf.c ft_printf/ft_uitoa.c

SRC_BONUS = ft_lstadd_front.c ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstiter.c ft_lstclear.c ft_lstmap.c

CFLAGS = -Wall -Wextra -Werror
CC = clang
AR = ar -crs
NAME = libft.a

DIR = .

OBJS = $(addprefix $(DIR)/,$(SRC:%.c=%.o))
PRINTF_OBJS = $(addprefix $(DIR)/,$(PRINTF:%.c=%.o))
OBJS_BONUS = $(addprefix $(DIR)/,$(SRC_BONUS:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_BONUS) $(PRINTF_OBJS)
	$(AR) $(NAME) $(OBJS) $(OBJS_BONUS) $(PRINTF_OBJS)

clean:
	rm -f $(DIR)/*.o $(DIR)/*.out
	rm -f $(DIR)/ft_printf/*.o

fclean: clean
	rm -f  $(DIR)/$(NAME)

bonus: $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS_BONUS)

re: fclean $(NAME)

.PHONY: clean fclean all bonus re
