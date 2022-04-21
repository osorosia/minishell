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

char *create_env_name(char *str) {
    char *name;
    char *eq;

    eq = ft_strchr(str, '=');
    if (eq == NULL)
        name = ft_strdup(str);
    else
        name = ft_strndup(str, eq - str);
    if (name == NULL)
        error("malloc error");
    return name;
}

char *create_env_body(char *str) {
    char *body;
    char *eq;

    eq = ft_strchr(str, '=');
    if (eq == NULL)
        return NULL;
    body = ft_strdup(eq + 1);
    if (body == NULL)
        error("malloc error");
    return body;
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
