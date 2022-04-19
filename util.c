#include "minishell.h"

bool starts_with(const char *dest, const char *src) {
    const size_t len = ft_strlen(src);

    return ft_strncmp(dest, src, len) == 0;
}

void error(char *str) {
    ft_putstr_fd(str, 2);
    ft_putstr_fd("\n", 2);
    exit(1);
}
