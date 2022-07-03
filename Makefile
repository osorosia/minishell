NAME = minishell

OBJ_DIR += ./
SRCS += $(addprefix ./, \
	main.c \
	)
OBJ_DIR += utils/
SRCS += $(addprefix utils/, \
	error.c \
	ft_str_add_char.c \
	is_only_space.c \
	starts_with.c \
	syntax_error.c \
	x_dup.c \
	x_fork.c \
	x_pipe.c \
	)
OBJ_DIR += shell/
SRCS += $(addprefix shell/, \
	add_env.c \
	create_shell.c \
	del_env.c \
	env.c \
	env_utils.c \
	envp.c \
	free_env.c \
	get_env.c \
	new_env.c \
	)
OBJ_DIR += signal/
SRCS += $(addprefix signal/, \
	signai_exec.c \
	signal_heredoc.c \
	signal_init.c \
	)
OBJ_DIR += builtin/
SRCS += $(addprefix builtin/, \
	cd.c \
	echo.c \
	env.c \
	exit.c \
	export.c \
	is_builtin.c \
	pwd.c \
	unset.c \
	)
OBJ_DIR += lexer/
SRCS += $(addprefix lexer/, \
	free_lexer.c \
	lexer.c \
	lexer_utils.c \
	)
OBJ_DIR += parser/
SRCS += $(addprefix parser/, \
	bracket.c \
	cmd.c \
	free_parser.c \
	parser.c \
	parser_utils.c \
	parser_utils1.c \
	pipe_cmd.c \
	stmt.c \
	)
OBJ_DIR += expander/
SRCS += $(addprefix expander/, \
	delete_quote.c \
	expand_asterisk.c \
	expand_asterisk1.c \
	expand_asterisk2.c \
	expand_var.c \
	expand_var1.c \
	expander.c \
	expander_set_heredoc.c \
	expander_utils.c \
	generate_pathname.c \
	generate_pathname1.c \
	split_space.c \
	)
OBJ_DIR += exec/
SRCS += $(addprefix exec/, \
	exec.c \
	exec_bracket.c \
	exec_builtin.c \
	exec_cmd.c \
	exec_file.c \
	exec_pipe.c \
	exec_stmt.c \
	exec_utils.c \
	)
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
	@cd .test && cat test.sh case.sh > temp.sh && bash temp.sh 2>/dev/null
else
	@cd .test && cat test.sh case.sh > temp.sh && zsh temp.sh 2>/dev/null
endif

leak: all
ifeq ($(OS), Linux)
	@cd .test && cat leak.sh case.sh > temp.sh && bash temp.sh 2>/dev/null
else
	@cd .test && cat leak.sh case.sh > temp.sh && zsh temp.sh 2>/dev/null
endif

gen: all
	cd .test/gen && bash gen.sh
ifeq ($(OS), Linux)
	@cd .test && cat test.sh init.sh case_gen.sh > temp.sh && bash temp.sh 2>/dev/null
	@cd .test && cat leak.sh init.sh case_gen.sh > temp.sh && bash temp.sh 2>/dev/null
else
	@cd .test && cat test.sh init.sh case_gen.sh > temp.sh && zsh temp.sh 2>/dev/null
	@cd .test && cat leak.sh init.sh case_gen.sh > temp.sh && zsh temp.sh 2>/dev/null
endif

msg: all
ifeq ($(OS), Linux)
	@cd .test && cat msg.sh init.sh case_msg.sh > temp.sh && bash temp.sh
else
	@cd .test && cat msg.sh init.sh case_msg.sh > temp.sh && zsh temp.sh
endif

.PHONY: all clean fclean re bonus
.PHONY: norm n ok leak gen msg
