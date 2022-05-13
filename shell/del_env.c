#include "../minishell.h"

void del_env(char *name) {
    t_env *env = g_shell->env;
    t_env *prev;
    long i = 0;
    while (env) {
        if (ft_strcmp(name, env->name) == 0) {
            if (i == 0) {
                g_shell->env = env->next;
            } else {
                prev->next = env->next;
            }
            free_env(env);
            return;
        }
        i++;
        prev = env;
        env = env->next;
    }
}
