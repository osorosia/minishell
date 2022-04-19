NAME = minishell
NAME = minishell
SRCS = $(wildcard *.c) \
	$(wildcard ./lexer/*.c)

OBJS = $(SRCS:.c=.o)
# CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
READLINE = -L/usr/include -lreadline

$(NAME): $(OBJS) $(LIBFT) ./minishell.h
	gcc $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(READLINE)

$(LIBFT):
	make -C ./libft

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) $(DEBUG) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	python3 -m norminette $(SRCS) | grep Error | cat

# test:
# 	cd tests && bash test.sh 2>/dev/null
