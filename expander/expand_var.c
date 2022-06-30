#include "../minishell.h"

bool _is_var_first_name_char(char c) {
    return ft_isalpha(c) || c == '_';
}

bool _is_var_name_char(char c) {
    return ft_isalnum(c) || c == '_';
}

char *_get_var_name(char *str) {
    char *name;
    long len;

    len = 0;
    while (str[len] && _is_var_name_char(str[len]))
        len++;
    name = ft_xstrndup(str, len);
    return name;
}

char *_expand_var_in_str(char *str) {
    char *new;
    long i;
    bool double_quote;
    bool single_quote;

    new = ft_xstrdup("");
    double_quote = false;
    single_quote = false;
    i = 0;
    while (str[i]) {
        if (!single_quote && str[i] == '$' && str[i + 1] == '?') {
            char *sts = ft_itoa(g_shell->sts);
            if (sts == NULL)
                error("malloc error");
            new = ft_xstrjoin_with_free(new, true, sts, true);
            i += 2;
            continue;
        }
        if (!single_quote && str[i] == '$' && !_is_var_first_name_char(str[i + 1])) {
            new = ft_xstrjoin_with_free(new, true, "$", false);
            i++;
            continue;
        }
        if (!single_quote && str[i] == '$') {
            i++;
            char *name = _get_var_name(&str[i]);
            if (name[0] != '\0') {
                char *body = get_env_body(name);
                new = ft_xstrjoin_with_free(new, true, body, false);
                i += ft_strlen(name);
            }
            free(name);
            continue;
        }
        if (str[i] == '"' && !single_quote)
            double_quote = !double_quote;
        if (str[i] == '\'' && !double_quote)
            single_quote = !single_quote;
        new = ft_str_add_char(new, str[i]);
        i++;
    }
    free(str);
    return new;
}

void _expand_var_in_redir(t_redir *redir) {
    if (redir == NULL)
        return;
    if (redir->kind != RD_HEREDOC)
        redir->str = _expand_var_in_str(redir->str);
    _expand_var_in_redir(redir->next);
}

void _expand_var_in_word(t_word *word) {
    if (word == NULL)
        return;
    word->str = _expand_var_in_str(word->str);
    _expand_var_in_word(word->next);
}

void expand_var(t_node *node) {
    if (node == NULL)
        return;
    if (node->kind == ND_STMT)
        return;
    if (node->kind == ND_CMD) {
        _expand_var_in_word(node->cmd->word);
        _expand_var_in_redir(node->cmd->redir_in);
        _expand_var_in_redir(node->cmd->redir_out);
    }
    else {
        expand_var(node->lhs);
        expand_var(node->rhs);
    }
}

void expand_var_for_debug(t_node *node) {
    if (node == NULL)
        return;
    // if (node->kind == ND_STMT)
    //     return;
    if (node->kind == ND_CMD) {
        _expand_var_in_word(node->cmd->word);
        _expand_var_in_redir(node->cmd->redir_in);
        _expand_var_in_redir(node->cmd->redir_out);
    }
    else {
        expand_var_for_debug(node->lhs);
        expand_var_for_debug(node->rhs);
    }
}
