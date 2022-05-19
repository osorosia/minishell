#include "../minishell.h"

t_env *new_env(char *name, char *body) {
    t_env *env = ft_calloc(1, sizeof(t_env));
    if (env == NULL)
        error("malloc error");
    env->name = name;
    env->body = body;
    return env;
}
