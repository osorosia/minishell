#include "../minishell.h"

bool is_only_space(char *str) {
    long i;
    
    i = 0;
    while (str[i]) {
        if (str[i] != ' ')
            return false;
        i++;
    }
    return true;
}
