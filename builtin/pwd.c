#include "../minishell.h"

int exec_pwd(t_word *word) {
    char cwd[PATH_MAX + 1];
    getcwd(cwd, sizeof(cwd));
    ft_putstr_fd(cwd, 1);
    ft_putstr_fd("\n", 1);

    return 0;
}
