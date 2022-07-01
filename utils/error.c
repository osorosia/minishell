#include "../minishell.h"

void error(char *str) {
    ft_putendl_fd(str, 2);
    exit(1);
}
