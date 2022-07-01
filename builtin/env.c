#include "../minishell.h"

int exec_env(t_word *word) {
    t_env *env = g_shell->env;
    while (env) {
        if (env->body)
            ft_printf("%s=%s\n", env->name, env->body);
        env = env->next;
    }
    return 0;
}
