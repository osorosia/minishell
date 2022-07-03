/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:40:22 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/03 11:19:26 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <signal.h>

# include "./libft/libft.h"

# define INDENT 4

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef enum e_token_kind	t_token_kind;
enum e_token_kind {
	TK_WORD,
	TK_OP,
	TK_EOF,
};

typedef enum e_node_kind	t_node_kind;
enum e_node_kind {
	ND_STMT,
	ND_AND,
	ND_OR,
	ND_PIPE,
	ND_CMD,
	ND_BRACKET,
};

typedef enum e_redir_kind	t_redir_kind;
enum e_redir_kind {
	RD_OUT,
	RD_IN,
	RD_APPEND,
	RD_HEREDOC,
};

typedef struct s_token		t_token;
struct s_token {
	t_token_kind	kind;
	t_token			*next;
	char			*str;
	long			len;
};

// parser

typedef struct s_redir		t_redir;
struct s_redir {
	t_redir_kind	kind;
	t_redir			*next;
	char			*str;
	int				fd;
};

typedef struct s_word		t_word;
struct s_word {
	t_word	*next;
	char	*str;
};

typedef struct s_cmd		t_cmd;
struct s_cmd {
	t_word	*word;
	t_redir	*redir_in;
	t_redir	*redir_out;
	bool	is_builtin;
	char	*pathname;
};

typedef struct s_node		t_node;
struct s_node {
	t_node_kind	kind;
	t_node		*lhs;
	t_node		*rhs;
	t_cmd		*cmd;
};

// shell

typedef struct s_env		t_env;
struct s_env {
	t_env	*next;
	char	*name;
	char	*body;
};

typedef struct s_shell		t_shell;
struct s_shell {
	t_env	*env;
	int		sts;
	int		fd_stdout;
	int		fd_stdin;
	bool	interrupt;
	bool	is_test;
};

//
// utils ----------------------------------------------
//

bool	starts_with(const char *dest, const char *src);
void	error(char *str);
char	*ft_str_add_char(char *str, char c);
bool	is_only_space(char *str);
void	syntax_error(char *str, long len);
pid_t	x_fork(void);
int		x_pipe(int fd[2]);
int		x_dup(int fd);
int		x_dup2(int fd1, int fd2);

//
// builtin ----------------------------------------------
//

// is_builtin.c
bool	is_builtin(char *str);
int		builtin_echo(t_word *word);
int		builtin_cd(t_word *word);
int		builtin_pwd(t_word *word);
int		builtin_export(t_word *word);
int		builtin_unset(t_word *word);
int		builtin_env(t_word *word);
int		builtin_exit(t_word *word);

//
// lexer ----------------------------------------------
//

// lexer.c
t_token	*lexer(char *p);
// lexer_utils.c
t_token	*skip(t_token *tok, t_token_kind kind, char *str);
bool	equal(t_token *tok, t_token_kind kind, char *str);
// free_lexer.c
void	free_lexer(t_token *tok);

//
// parser ----------------------------------------------
//

// parser.c
t_node	*parser(t_token *tok);
t_node	*stmt(t_token **tok);
t_node	*bracket(t_token **tok);
t_node	*pipe_cmd(t_token **tok);
t_node	*cmd(t_token **tok);
// free_parser.c
void	free_parser(t_node *node);
// parser_utils.c
t_node	*_new_node_stmt(t_node_kind kind, t_node *pipe_cmd_node);
void	_add_node_stmt(t_node *node, t_node_kind kind, t_node *bracket_node);
void	*_new_node_bracket(t_node *stmt_node);
t_node	*_new_node_pipe(t_node *cmd_node);
t_node	*_add_node_pipe(t_node *node, t_node *cmd_node);
t_node	*_new_node_cmd(void);
void	_add_word(t_cmd *cmd, char *str, long len);
void	_add_redir_in(t_cmd *cmd, t_redir_kind kind, char *str, long len);
void	_add_redir_out(t_cmd *cmd, t_redir_kind kind, char *str, long len);

//
// expander ----------------------------------------------
//

// expander.c
void	expander(t_node *node);
// expand_var.c
void	expand_var(t_node *node);
long	_expand_var_at_doller_mark(char *str, char **new, long i);
char	*_get_var_name(char *str);
// generate_pathname.c
void	generate_pathname(t_node *node);
// split_space.c
void	split_space(t_node *node);
// delete_quote.c
void	delete_quote(t_node *node);
void	delete_quote_in_heredoc(t_redir *redir);
// expander_set_heredoc.c
void	expander_set_heredoc(t_node *node);
// expander_utils.c
bool	is_var_name_char(char c);
bool	is_var_name_char_1st(char c);

//
// exec ----------------------------------------------
//
void	exec(t_node *node);
void	exec_cmd(t_node *node);
void	exec_bracket(t_node *pipe_node);
void	exec_pipe(t_node *pipe_node);
void	exec_stmt(t_node *stmt_node);

//
// shell ----------------------------------------------
//

// shell.c
t_shell	*create_shell(char **envp);
// env.c
t_env	*create_env(char **envp);
// get_env.c
char	*get_env_body(char *name);
// envp.c
char	**create_envp(void);
void	free_envp(char **envp);
// free_env.c
void	free_env(t_env *env);
// new_env.c
t_env	*new_env(char *name, char *body);
// del_env.c
void	del_env(char *name);
// add_env.c
void	add_env(char *str);
void	add_env_plus(char *str);
// env_utils.c
char	*create_env_name(char *str);
char	*create_env_body(char *str);
char	*create_env_name_plus(char *str);
char	*create_env_body_plus(char *str);

// signal ---------------------------------------------

void	signal_exec(void);
void	signal_init(void);
void	signal_heredoc(void);

// grobal variable ------------------------------------

t_shell						*g_shell;

#endif
