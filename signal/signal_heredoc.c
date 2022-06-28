#include "../minishell.h"

void _sigint_heredoc(int signal) {
    // TODO
    g_shell->interrupt = true;
}

void signal_heredoc() {
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, _sigint_heredoc);
}
