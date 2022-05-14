#include "../minishell.h"


void show_envs() {
    t_env *env = g_shell->env;
    while (env) {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(env->name, 1);
        if (env->body) {
            ft_putstr_fd("=\"", 1);
            ft_putstr_fd(env->body, 1);
            ft_putstr_fd("\"", 1);
        }
        ft_putstr_fd("\n", 1);
        env = env->next;
    }
}

int exec_export(t_word *word) {
    if (word->next == NULL) {
        show_envs();
        return 0;
    }
    word = word->next;
    while (word) {
        if (ft_strncmp(word->str, "+=", 2) == 0 || word->str[0] == '=') {
            ft_putstr_fd("export: `", 2);
            ft_putstr_fd(word->str, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
        } else if (ft_strnstr(word->str, "+=", ft_strlen(word->str))) {
            add_env_plus(word->str);
        } else {
            add_env(word->str);
        }
        word = word->next;
    }
    return 0;
}
