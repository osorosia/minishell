NAME = minishell
SRCS = $(wildcard *.c) \
	$(wildcard ./utils/*.c) \
	$(wildcard ./shell/*.c) \
	$(wildcard ./signal/*.c) \
	$(wildcard ./builtin/*.c) \
	$(wildcard ./lexer/*.c) \
	$(wildcard ./parser/*.c) \
	$(wildcard ./expander/*.c) \
	$(wildcard ./exec/*.c) \

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

OS = $(shell uname)
ifeq ($(OS), Linux)
	CFLAGS = -g3
	READLINE = -L/usr/include -lreadline
else
	CFLAGS = -g3 -I $(shell brew --prefix readline)/include 
	READLINE = -L/usr/include -lreadline -lhistory -L$(shell brew --prefix readline)/lib
endif

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

.PHONY: ok
ok: all
ifeq ($(OS), Linux)
	@cd tests && cat test.sh case.sh > temp.sh && bash temp.sh 2>/dev/null
else
	@cd tests && cat test.sh case.sh > temp.sh && zsh temp.sh 2>/dev/null
endif

.PHONY: leak
leak: all
ifeq ($(OS), Linux)
	@cd tests && cat leak.sh case.sh > temp.sh && bash temp.sh 2>/dev/null
else
	@cd tests && cat leak.sh case.sh > temp.sh && zsh temp.sh 2>/dev/null
endif

.PHONY: gen
gen: all
	cd tests/gen && bash gen.sh
ifeq ($(OS), Linux)
	@cd tests && cat test.sh gen_case.sh > temp.sh && bash temp.sh 2>/dev/null
	@cd tests && cat leak.sh gen_case.sh > temp.sh && bash temp.sh 2>/dev/null
else
	@cd tests && cat test.sh gen_case.sh > temp.sh && zsh temp.sh 2>/dev/null
	@cd tests && cat leak.sh gen_case.sh > temp.sh && zsh temp.sh 2>/dev/null
endif

.PHONY: msg
msg: all
ifeq ($(OS), Linux)
	@cd tests && cat msg.sh msg_case.sh > temp.sh && bash temp.sh
else
	@cd tests && cat msg.sh msg_case.sh > temp.sh && zsh temp.sh
endif
