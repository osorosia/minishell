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

#include "./libft/libft.h"

typedef enum e_token_kind t_token_kind;
enum e_token_kind {
    TK_WORD,
    TK_OP,
    TK_EOF,
};

typedef struct s_token t_token;
struct s_token {
    t_token_kind kind;

    t_token *next;
    char *str;
    long len;
};


// utils.c
bool starts_with(const char *dest, const char *src);
void error(char *str);

//
// lexer
//

// lexer.c
t_token *lexer(char *p);
// debug_lexer.c
void debug_lexer(t_token *tok);


#endif
