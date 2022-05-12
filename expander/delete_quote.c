#include "../minishell.h"

char *_delete_quote_in_str(char *str) {
    char *new;

    new = NULL;
    long i = 0;
    while (str[i]) {
        if (str[i] != '\'' && str[i] != '"')
            new = ft_str_add_char(new, str[i]);
        i++;
    }
    free(str);
    return new;
}

void _delete_quote_in_redir(t_redir *redir) {
    if (redir == NULL)
        return;
    redir->str = _delete_quote_in_str(redir->str);
    _delete_quote_in_redir(redir->next);
}

void _delete_quote_in_word(t_word *word) {
    if (word == NULL)
        return;
    word->str = _delete_quote_in_str(word->str);
    _delete_quote_in_word(word->next);
}

void delete_quote(t_node *node) {
    if (node == NULL)
        return;
    if (node->kind == ND_CMD) {
        _delete_quote_in_word(node->cmd->word);
        _delete_quote_in_redir(node->cmd->redir_in);
        _delete_quote_in_redir(node->cmd->redir_out);
    } else {
        delete_quote(node->lhs);
        delete_quote(node->rhs);
    }
}
