#include "../minishell.h"

void _sigint_exec(int signal) {
    g_shell->interrupt = true;
    ft_putstr_fd("\n", 2);
}

void signal_exec() {
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, _sigint_exec);
}
