#include "../minishell.h"

void free_paths(char **paths) {
    long i = 0;
    while (paths[i]) {
        free(paths[i]);
        i++;
    }
    free(paths);
}

bool check_pathname(char *pathname) {
    struct stat st;
    
    if (access(pathname, F_OK) != 0)
        return false;
    if (stat(pathname, &st) != 0)
        return false;
    return !S_ISDIR(st.st_mode);
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
        base = ft_xstrjoin(paths[i], "/");
        pathname = ft_xstrjoin_with_free(base, true, str, false);
        if (check_pathname(pathname)) {
            free_paths(paths);
            return pathname;
        }
        free(pathname);
        i++;
    }
    free_paths(paths);
    return NULL;
}

char *get_pathname_str(char *str) {
    char *pathname;

    if (ft_strchr(str, '/')) {
        pathname = ft_strdup(str);
        if (pathname == NULL) {
            error("malloc error");
        }
    }
    else
        pathname = find_pathname(str);
    return pathname;
}

void generate_pathname(t_node *node) {
    if (node == NULL)
        return;
    if (node->kind == ND_STMT)
        return;
    if (node->kind == ND_CMD) {
        if (node->cmd->word == NULL)
            return;
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
        if (node->cmd->word == NULL)
            return;
        if (is_builtin(node->cmd->word->str))
            node->cmd->is_builtin = true;
        else
            node->cmd->pathname = get_pathname_str(node->cmd->word->str);
    }
    else {
        generate_pathname_for_debug(node->lhs);
        generate_pathname_for_debug(node->rhs);
    }
}
