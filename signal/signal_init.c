#include "../minishell.h"

void _sigint_init(int signal) {
    (void)signal;
    ft_putstr_fd("\n", 2);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    g_shell->sts = 128 + SIGINT;
}

void signal_init() {
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, _sigint_init);
}
