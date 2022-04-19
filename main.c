#include "minishell.h"

int main(int argc, char **argv, char **envp) {
    t_token *tok;
    t_node *node;

    rl_outstream = stderr;

    g_shell = create_shell(envp);
    debug_env();
    
    while (true) {
        char *str = readline("minishell$ ");
        
        if (str == NULL)
            exit(0);
        if (str[0] == '\0') {
            free(str);
            continue;
        }
        add_history(str);

        printf("%s\n", str);

        // lexer
        tok = lexer(str);
        debug_lexer(tok);

        // parser
        node = parser(tok);
        debug_parser(node);
        free_lexer(tok);

        // expander
        // expander(node);

        free_parser(node);
        free(str);
    }
}
