#include "../minishell.h"

char *ft_strjoin_with_free(char *s1, bool f1, char *s2, bool f2) {
    char *str = ft_strjoin(s1, s2);
    if (str == NULL)
        error("malloc error");
    if (f1)
        free(s1);
    if (f2)
        free(s2);
    return str;
}
