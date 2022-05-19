#include "minishell.h"

void print_status() {
    if (g_shell->sts != 0)
        ft_putstr_fd("\033[0;31m", 2);
    ft_putstr_fd("[", 2);
    ft_putnbr_fd(g_shell->sts, 2);
    ft_putstr_fd("] ", 2);
    if (g_shell->sts != 0)
        ft_putstr_fd("\033[0m", 2);
    
    char cwd[PATH_MAX + 1];
    getcwd(cwd, sizeof(cwd));
    ft_putstr_fd(cwd, 2);
    ft_putstr_fd("\n", 2);
}

int main(int argc, char **argv, char **envp) {
    t_token *tok;
    t_node *node;

    rl_outstream = stderr;

    g_shell = create_shell(envp);
    if (argc >= 2)
        g_shell->is_debug = true;
    if (g_shell->is_debug)
        debug_env();
    
    while (true) {
        signal_init();
        if (g_shell->is_debug)
            print_status();
        char *str = readline("minishell$ ");
        
        if (str == NULL)
            break;
        if (is_only_space(str)) {
            free(str);
            continue;
        }
        add_history(str);

        // printf("%s\n", str);
        {
            int pid = fork();
            if (pid == 0) {
                tok = lexer(str);
                node = parser(tok);
                exit(0);
            }
            int sts;
            wait(&sts);

            if (sts != 0) {
                free(str);
                g_shell->sts = 258;
                continue;
            }
        }

        // lexer
        tok = lexer(str);
        if (g_shell->is_debug)
            debug_lexer(tok);

        // parser
        node = parser(tok);
        if (g_shell->is_debug)
            debug_parser(node);

        // expander
        if (g_shell->is_debug) {
            t_node *tmp = parser(tok);
            expander_for_debug(tmp);
            free_parser(tmp);
        }
        free_lexer(tok);

        if (g_shell->is_debug)
            ft_putstr_fd("--- heredoc ---\n", 2);
        expander_set_heredoc(node);
        if (g_shell->is_debug)   
            debug_expander(node, "set_heredoc");

        // exec
        if (g_shell->is_debug)
            fprintf(stderr, "--- exec ---\n");
        exec(node);

        free_parser(node);
        free(str);
    }
    ft_putstr_fd("exit\n", 2);
    exit(g_shell->sts);
}
