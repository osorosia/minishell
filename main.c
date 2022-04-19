#include "minishell.h"

int main(int argc, char **argv, char **envp) {
    t_token *tok;
    
    while (true) {
        char *str = readline("minishell$ ");
        add_history(str);

        printf("%s\n", str);
        // lexer
        tok = lexer(str);
        debug_lexer(tok);
        free_lexer(tok);
        free(str);
    }
}
