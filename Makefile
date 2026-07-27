NAME		= push_swap
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -Iincludes -Ilibft
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
SRC_DIR     = srcs

SRCS = \
	main.c \
	parse.c \
	stack.c \
	ops_swap.c \
	ops_push.c \
	ops_rotate.c \
	ops_rrotate.c \
	disorder.c \
	sort_simple.c \
	sort_medium.c \
	sort_complex.c \
	sort_adaptive.c \
	sort_small.c \
	bench.c \
	utils.c

OBJS = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c includes/push_swap.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
