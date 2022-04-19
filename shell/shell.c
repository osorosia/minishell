#include "../minishell.h"

t_shell *create_shell(char **envp) {
    t_shell *shell;

    shell = ft_calloc(1, sizeof(t_shell));
    if (shell == NULL)
        error("malloc error");
    shell->env = create_env(envp);
    return shell;
}
