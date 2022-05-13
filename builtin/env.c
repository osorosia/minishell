#include "../minishell.h"

int exec_env(t_word *word) {
    t_env *env = g_shell->env;
    while (env) {
        ft_putstr_fd(env->name, 1);
        if (env->body) {
            ft_putstr_fd("=", 1);
            ft_putstr_fd(env->body, 1);
        }
        ft_putstr_fd("\n", 1);
        env = env->next;
    }
    return 0;
}
