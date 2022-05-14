#include "../minishell.h"

t_env *add_new_env(t_env *env, char *name, char *body) {
    t_env *now;
    t_env *new;

    new = ft_calloc(1, sizeof(t_env));
    if (new == NULL)
        error("malloc error");
    new->name = name;
    new->body = body;
    if (env == NULL)
        return new;
    else {
        now = env;
        while (now->next)
            now = now->next;
        now->next = new;
    }
    return env;
}

t_env *create_env(char **envp) {
    t_env *env;
    long i;

    env = NULL;
    i = 0;
    while (envp[i]) {
        env = add_new_env(env, create_env_name(envp[i]), create_env_body(envp[i]));
        i++;
    }
    return (env);
}
