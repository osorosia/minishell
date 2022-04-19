#include "minishell.h"

int main(int argc, char **argv, char **envp) {
    t_token *tok;
    t_node *node;
    
    while (true) {
        char *str = readline("minishell$ ");
        add_history(str);

        printf("%s\n", str);

        // lexer
        tok = lexer(str);
        debug_lexer(tok);
        
        // parser
        node = parser(tok);
        free_lexer(tok);

        debug_parser(node);
        free_parser(node);

        free(str);
    }
}
