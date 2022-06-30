#include "../minishell.h"

char *ft_str_add_char(char *str, char c) {
    char ch[2];

    ch[0] = c;
    ch[1] = '\0';
    return ft_xstrjoin_with_free(str, true, ch, false);
}
