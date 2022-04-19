#include "../minishell.h"

void debug_lexer(t_token *tok) {
    const char *kind[] = {"TK_WORD", "TK_OP", "TK_EOF"};

    fprintf(stderr, "lexer {\n");
    while (tok) {
        fprintf(stderr, "    {kind: %7s, str: %.*s}\n",
            kind[tok->kind], (int)tok->len, tok->str);
        tok = tok->next;
    }
    fprintf(stderr, "}\n");
}
