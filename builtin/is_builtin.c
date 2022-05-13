#include "../minishell.h"

bool is_builtin(char *str) {
    char *kw[] = {/*"echo",*/ "cd", "pwd", "export", "unset", "env", "exit", NULL};
    // char *kw[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

    long i = 0;
    while (kw[i]) {
        if (ft_strcmp(kw[i], str) == 0)
            return true;
        i++;
    }
    return false;
}
