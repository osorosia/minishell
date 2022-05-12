NAME = minishell
SRCS = $(wildcard *.c) \
	$(wildcard ./utils/*.c) \
	$(wildcard ./shell/*.c) \
	$(wildcard ./lexer/*.c) \
	$(wildcard ./parser/*.c) \
	$(wildcard ./expander/*.c) \
	$(wildcard ./exec/*.c) \

OBJS = $(SRCS:.c=.o)
# CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -g
LIBFT = ./libft/libft.a
READLINE = -L/usr/include -lreadline

$(NAME): $(OBJS) $(LIBFT) ./minishell.h
	gcc $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(READLINE)

$(LIBFT):
	make -C ./libft

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: norm
re: fclean all

.PHONY: norm
norm:
	python3 -m norminette $(SRCS) | grep Error | cat

.PHONY: test
test: all
	cd tests && ./test.sh 2>/dev/null
	cd ./tests/testcase && ./diff.sh 2>/dev/null
	cat ./tests/testcase/diff_file
.PHONY:all fclean clean re norm t test
