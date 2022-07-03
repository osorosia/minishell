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
CFLAGS = -Wall -Wextra -Werror

OS = $(shell uname)
ifeq ($(OS), Linux)
	CFLAGS += -g3
	READLINE = -L/usr/include -lreadline
else
	CFLAGS += -g3 -I $(shell brew --prefix readline)/include 
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

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

norm:
	norminette $(SRCS) minishell.h libft | grep -v 'OK!' || echo norm: OK

n:
	norminette $(SRCS) minishell.h libft | grep Error! || echo norm: OK

ok: all
ifeq ($(OS), Linux)
	@cd tests && cat test.sh case.sh > temp.sh && bash temp.sh 2>/dev/null
else
	@cd tests && cat test.sh case.sh > temp.sh && zsh temp.sh 2>/dev/null
endif

leak: all
ifeq ($(OS), Linux)
	@cd tests && cat leak.sh case.sh > temp.sh && bash temp.sh 2>/dev/null
else
	@cd tests && cat leak.sh case.sh > temp.sh && zsh temp.sh 2>/dev/null
endif

gen: all
	cd tests/gen && bash gen.sh
ifeq ($(OS), Linux)
	@cd tests && cat test.sh init.sh case_gen.sh > temp.sh && bash temp.sh 2>/dev/null
	@cd tests && cat leak.sh init.sh case_gen.sh > temp.sh && bash temp.sh 2>/dev/null
else
	@cd tests && cat test.sh init.sh case_gen.sh > temp.sh && zsh temp.sh 2>/dev/null
	@cd tests && cat leak.sh init.sh case_gen.sh > temp.sh && zsh temp.sh 2>/dev/null
endif

msg: all
ifeq ($(OS), Linux)
	@cd tests && cat msg.sh init.sh case_msg.sh > temp.sh && bash temp.sh
else
	@cd tests && cat msg.sh init.sh case_msg.sh > temp.sh && zsh temp.sh
endif

.PHONY: all clean fclean re bonus
.PHONY: norm n ok leak gen msg
