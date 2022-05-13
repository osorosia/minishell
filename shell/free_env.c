#include "../minishell.h"

void free_env(t_env *env) {
    free(env->name);
    free(env->body);
    free(env);
}
