NAME = minishell

OBJ_DIR += ./
SRCS += $(wildcard *.c)
OBJ_DIR += utils/
SRCS += $(wildcard utils/*.c)
OBJ_DIR += shell/
SRCS += $(wildcard shell/*.c)
OBJ_DIR += signal/
SRCS += $(wildcard signal/*.c)
OBJ_DIR += builtin/
SRCS += $(wildcard builtin/*.c)
OBJ_DIR += lexer/
SRCS += $(wildcard lexer/*.c)
OBJ_DIR += parser/
SRCS += $(wildcard parser/*.c)
OBJ_DIR += expander/
SRCS += $(wildcard expander/*.c)
OBJ_DIR += exec/
SRCS += $(wildcard exec/*.c)

OBJS = $(SRCS:%.c=obj/%.o)
OBJ_DIR := $(addprefix obj/, $(OBJ_DIR))
OBJ_DIR := $(addsuffix .keep, $(OBJ_DIR))

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

obj/%.o: %.c $(OBJ_DIR)
	gcc $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(@D)
	touch $@

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
	python3 -m norminette $(SRCS) minishell.h | grep Error | cat

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
	@cd tests && cat test.sh init.sh case_gen.sh > temp.sh && bash temp.sh 2>/dev/null
	@cd tests && cat leak.sh init.sh case_gen.sh > temp.sh && bash temp.sh 2>/dev/null
else
	@cd tests && cat test.sh init.sh case_gen.sh > temp.sh && zsh temp.sh 2>/dev/null
	@cd tests && cat leak.sh init.sh case_gen.sh > temp.sh && zsh temp.sh 2>/dev/null
endif

.PHONY: msg
msg: all
ifeq ($(OS), Linux)
	@cd tests && cat msg.sh init.sh case_msg.sh > temp.sh && bash temp.sh
else
	@cd tests && cat msg.sh init.sh case_msg.sh > temp.sh && zsh temp.sh
endif
