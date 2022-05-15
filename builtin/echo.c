#include "../minishell.h"

bool is_opt_n(char *str) {
    if (ft_strncmp(str, "-n", 2) != 0) {
        return false;
    }
    long i = 1;
    while (str[i]) {
        if (str[i] != 'n')
            return false;
        i++;
    }
    return true;
}

int exec_echo(t_word *word) {
    bool opt_n = false;
    t_word *w = word->next;

    while (w && is_opt_n(w->str)) {
        opt_n = true;
        w = w->next;
    }

    while (w) {
        ft_putstr_fd(w->str, 1);
        w = w->next;
        if (w)
            ft_putstr_fd(" ", 1);
    }

    if (!opt_n) {
        ft_putstr_fd("\n", 1);
    }

    return 0;
}
