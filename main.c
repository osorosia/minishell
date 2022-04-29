#include "minishell.h"

void print_status() {
    ft_putstr_fd("[", 2);
    ft_putnbr_fd(g_shell->sts, 2);
    ft_putstr_fd("]", 2);
}

int main(int argc, char **argv, char **envp) {
    t_token *tok;
    t_node *node;

    rl_outstream = stderr;

    g_shell = create_shell(envp);
    debug_env();
    
    while (true) {
        print_status();
        char *str = readline("minishell$ ");
        
        if (str == NULL)
            exit(0);
        if (str[0] == '\0') {
            free(str);
            continue;
        }
        add_history(str);

        // printf("%s\n", str);

        // lexer
        tok = lexer(str);
        debug_lexer(tok);

        // parser
        node = parser(tok);
        debug_parser(node);

        // expander
        {
            t_node *tmp = parser(tok);
            expander_and_debug(tmp);
            free_parser(tmp);
        }
        free_lexer(tok);
        expander(node);

        // exec
        fprintf(stderr, "--- exec ---\n");
        exec(node);

        free_parser(node);
        free(str);
    }
}
