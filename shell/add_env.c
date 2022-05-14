#include "../minishell.h"

// str: "name=body" or "name"
void add_env(char *str) {
    char *name = create_env_name(str);
    char *body = create_env_body(str);

    if (g_shell->env == NULL) {
        g_shell->env = new_env(name, body);
        return;
    }
    t_env *env = g_shell->env;
    while (env->next) {
        if (ft_strcmp(env->name, name) == 0) {
            free(name);
            if (body) {
                free(env->body);
                env->body = body;
            }
            return;
        }
        env = env->next;
    }
    if (ft_strcmp(env->name, name) == 0) {
        free(name);
        if (body) {
            free(env->body);
            env->body = body;
        }
    } else {
        env->next = new_env(name, body);
    }
}

// str: "name+=body"
void add_env_plus(char *str) {
    char *name = create_env_name_plus(str);
    char *body = create_env_body_plus(str);

    if (g_shell->env == NULL) {
        g_shell->env = new_env(name, body);
        return;
    }
    t_env *env = g_shell->env;
    while (env->next) {
        if (ft_strcmp(env->name, name) == 0) {
            free(name);
            env->body = ft_strjoin_with_free(env->body, true, body, true);
            return;
        }
        env = env->next;
    }
    if (ft_strcmp(env->name, name) == 0) {
        free(name);
        env->body = ft_strjoin_with_free(env->body, true, body, true);
    } else {
        env->next = new_env(name, body);
    }
}
