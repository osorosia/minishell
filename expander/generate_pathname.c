#include "../minishell.h"

void free_paths(char **paths) {
    long i = 0;
    while (paths[i]) {
        free(paths[i]);
        i++;
    }
    free(paths);
}

char *find_pathname(char *str) {
    char **paths;
    char *base;
    char *pathname;

    paths = ft_split(get_env_body("PATH"), ':');
    if (paths == NULL) {
        str = ft_strdup(str);
        if (str == NULL)
            error("malloc error");
        return str;
    }

    long i = 0;
    while (paths[i]) {
        base = ft_strjoin(paths[i], "/");
        if (base == NULL)
            error("malloc error");
        pathname = ft_strjoin_with_free(base, true, str, false);
        if (access(pathname, F_OK) == 0) {
            free_paths(paths);
            return pathname;
        }
        free(pathname);
        i++;
    }
    free_paths(paths);
    return ft_strdup(str);
}

char *get_pathname_str(char *str) {
    char *pathname;

    if (ft_strchr(str, '/'))
        pathname = ft_strdup(str);
    else
        pathname = find_pathname(str);
    if (pathname == NULL)
        error("malloc error");
    return pathname;
}

void generate_pathname(t_node *node) {
    if (node == NULL)
        return;
    if (node->kind == ND_STMT)
        return;
    if (node->kind == ND_CMD) {
        if (is_builtin(node->cmd->word->str))
            node->cmd->is_builtin = true;
        else
            node->cmd->pathname = get_pathname_str(node->cmd->word->str);
    }
    else {
        generate_pathname(node->lhs);
        generate_pathname(node->rhs);
    }
}

void generate_pathname_for_debug(t_node *node) {
    if (node == NULL)
        return;
    // if (node->kind == ND_STMT)
    //     return;
    if (node->kind == ND_CMD) {
        node->cmd->pathname = get_pathname_str(node->cmd->word->str);
    }
    else {
        generate_pathname(node->lhs);
        generate_pathname(node->rhs);
    }
}
