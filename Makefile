NAME = minishell
SRCS = $(wildcard *.c) \
	$(wildcard ./utils/*.c) \
	$(wildcard ./lexer/*.c) \
	$(wildcard ./parser/*.c)

OBJS = $(SRCS:.c=.o)
# CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -g
LIBFT = ./libft/libft.a
READLINE = -L/usr/include -lreadline

$(NAME): $(OBJS) $(LIBFT) ./minishell.h
	gcc $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(READLINE)

$(LIBFT):
	make -C ./libft

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	python3 -m norminette $(SRCS) | grep Error | cat

# test:
# 	cd tests && bash test.sh 2>/dev/null
