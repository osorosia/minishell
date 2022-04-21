#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <signal.h>

#include "./libft/libft.h"

#define INDENT 4

typedef enum e_token_kind t_token_kind;
enum e_token_kind {
    TK_WORD,
    TK_OP,
    TK_EOF,
};

typedef enum e_node_kind t_node_kind;
enum e_node_kind {
    ND_STMT,
    ND_AND,
    ND_OR,
    ND_PIPE,
    ND_CMD,
};

typedef enum e_redir_kind t_redir_kind;
enum e_redir_kind {
    RD_OUT,
    RD_IN,
    RD_APPEND,
    RD_HEREDOC,
};

typedef struct s_token t_token;
struct s_token {
    t_token_kind kind;

    t_token *next;
    char *str;
    long len;
};

// parser

typedef struct s_redir t_redir;
struct s_redir {
    t_redir_kind kind;
    t_redir *next;
    char *str;
};

typedef struct s_word t_word;
struct s_word {
    t_word *next;
    char *str;
};

typedef struct s_cmd t_cmd;
struct s_cmd {
    t_word *word;
    t_redir *redir_in;
    t_redir *redir_out;
    bool is_builtin;
    char *pathname;
};

typedef struct s_node t_node;
struct s_node {
    t_node_kind kind;
    t_node *lhs;
    t_node *rhs;
    t_cmd *cmd;
};

// shell

typedef struct s_env t_env;
struct s_env {
    t_env *next;
    char *name;
    char *body;
};

typedef struct s_shell t_shell;
struct s_shell {
    t_env *env;
    int sts;
};

//
// utils ----------------------------------------------
//

bool starts_with(const char *dest, const char *src);
void error(char *str);
void print_indent(int indent);
char *ft_strjoin_with_free(char *s1, bool f1, char *s2, bool f2);
char *ft_str_add_char(char *str, char c);
bool ft_strcmp(char *s1, char *s2);

//
// lexer ----------------------------------------------
//

// lexer.c
t_token *lexer(char *p);
// lexer_utils.c
t_token *skip(t_token *tok, t_token_kind kind, char *str);
bool equal(t_token *tok, t_token_kind kind, char *str);
// debug_lexer.c
void debug_lexer(t_token *tok);
// free_lexer.c
void free_lexer(t_token *tok);

//
// parser ----------------------------------------------
//

// parser.c
t_node *parser(t_token *tok);
// debug_parser.c
void debug_parser(t_node *node);
// free_parser.c
void free_parser(t_node *node);

//
// expander ----------------------------------------------
//

// expander.c
void expander(t_node *node);
// debug_expander.c
void debug_expander(t_node *node, char *name);
// expand_var.c
void expand_var(t_node *node);
// generate_pathname.c
void generate_pathname(t_node *node);

//
// exec ----------------------------------------------
//
void exec(t_node *node);

//
// shell ----------------------------------------------
//

// shell.c
t_shell *create_shell(char **envp);
// env.c
t_env *create_env(char **envp);
// get_env.c
char *get_env_body(char *name);
// debug_env.c
void debug_env();

// grobal variable ------------------------------------

t_shell *g_shell;

#endif
