#include "../minishell.h"

int exec_unset(t_word *word) {
    word = word->next;
    while (word) {
        if (word->str)
            del_env(word->str);
        word = word->next;
    }
    return 0;
}
