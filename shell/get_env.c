#include "../minishell.h"

char *get_env_body(char *name) {
    t_env *env;

    env = g_shell->env;
    while (env) {
        if (ft_strcmp(name, env->name) == 0)
            return env->body;
        env = env->next;
    }
    return NULL;
}
