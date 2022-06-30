#include "../minishell.h"

t_env *new_env(char *name, char *body) {
    t_env *env;

    env = ft_xcalloc(1, sizeof(t_env));
    env->name = name;
    env->body = body;
    return env;
}
