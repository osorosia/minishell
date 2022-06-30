#include "../minishell.h"

void del_env(char *name) {
    t_env *env;
    t_env *prev;

    env = g_shell->env;
    while (env) {
        if (ft_strcmp(name, env->name) == 0) {
            if (env == g_shell->env) {
                g_shell->env = env->next;
            } else {
                prev->next = env->next;
            }
            free_env(env);
            return;
        }
        prev = env;
        env = env->next;
    }
}
