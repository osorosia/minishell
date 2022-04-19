#include "../minishell.h"

void free_lexer(t_token *tok) {
    t_token *next;

    while (tok) {
        next = tok->next;
        free(tok);
        tok = next;
    }
}
