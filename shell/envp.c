#include "../minishell.h"

long _get_env_size() {
    long sz = 0;
    t_env *env = g_shell->env;
    while (env) {
        if (env->body)
            sz++;
        env = env->next;
    }
    return sz;
}

char **create_envp() {
    long sz = _get_env_size();

    char **envp = ft_xcalloc(sz + 1, sizeof(char *));
    
    t_env *env = g_shell->env;
    long i = 0;
    while (env) {
        if (env->body) {
            envp[i] = ft_strjoin(env->name, "=");
            envp[i] = ft_strjoin_with_free(envp[i], true, env->body, false);
            i++;
        }
        env = env->next;
    }
    return envp;
}

void free_envp(char **envp) {
    long i = 0;
    while (envp[i]) {
        free(envp[i++]);
    }
    free(envp);
}
