#include "../minishell.h"

t_shell *create_shell(char **envp) {
    t_shell *shell;

    shell = ft_xcalloc(1, sizeof(t_shell));
    shell->env = create_env(envp);
    shell->stdout = dup(1);
    shell->stdin = dup(0);
    return shell;
}
