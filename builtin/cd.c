#include "../minishell.h"

int cd_home() {
    char *home = get_env_body("HOME");
    if (home == NULL) {
        ft_putstr_fd("cd: HOME not set\n", 2);
        return 1;
    }
    return 0;
}

int exec_cd(t_word *word) {
    // no args
    if (word->next == NULL) {
        return cd_home();        
    }

    if (word->next->next != NULL) {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return 1;
    }

    chdir(word->next->str);

    return 0;
}
