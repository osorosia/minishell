#include "../minishell.h"

bool starts_with(const char *dest, const char *src) {
    const size_t len = ft_strlen(src);

    return ft_strncmp(dest, src, len) == 0;
}
