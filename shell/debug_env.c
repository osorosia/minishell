#include "../minishell.h"

void debug_env() {
    t_env *env;

    env = g_shell->env;
    fprintf(stderr, "env {\n");
    while (env) {
        print_indent(INDENT);
        fprintf(stderr, "%s", env->name);
        if (env->body)
            fprintf(stderr, "=%s", env->body);
        fprintf(stderr, "\n");
        env = env->next;
    }
    fprintf(stderr, "}\n\n");
}
