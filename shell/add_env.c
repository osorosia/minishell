#include "../minishell.h"

// str: "name=body" or "name"
void add_env(char *str) {
    char *name = create_env_name(str);
    char *body = create_env_body(str);
    t_env *env;

    if (g_shell->env == NULL) {
        g_shell->env = new_env(name, body);
        return;
    }
    env = g_shell->env;
    while (true) {
        if (ft_strcmp(env->name, name) == 0) {
            free(name);
            if (body) {
                free(env->body);
                env->body = body;
            }
            return;
        }
        if (env->next == NULL) {
            env->next = new_env(name, body);
            return;
        }
        env = env->next;
    }
}

// str: "name+=body"
void add_env_plus(char *str) {
    char *name = create_env_name_plus(str);
    char *body = create_env_body_plus(str);
    t_env *env;

    if (g_shell->env == NULL) {
        g_shell->env = new_env(name, body);
        return;
    }
    env = g_shell->env;
    while (true) {
        if (ft_strcmp(env->name, name) == 0) {
            free(name);
            env->body = ft_xstrjoin_with_free(env->body, true, body, true);
            return;
        }
        if (env->next == NULL) {
            env->next = new_env(name, body);
            return;
        }
        env = env->next;
    }
}
