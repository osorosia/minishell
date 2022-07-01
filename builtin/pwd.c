#include "../minishell.h"

int exec_pwd(t_word *word) {
    char cwd[PATH_MAX + 1];
    ft_memset(cwd, 0, PATH_MAX + 1);
    getcwd(cwd, sizeof(cwd));
    ft_putendl_fd(cwd, 1);
    return 0;
}
