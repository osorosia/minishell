#include "../minishell.h"

t_token *skip(t_token *tok, t_token_kind kind, char *str) {
    if (tok->kind != kind)
        error("token error: unexpected token kind");
    if (str != NULL
        && (tok->len != ft_strlen(str) || ft_strncmp(tok->str, str, tok->len) != 0))
        error("token error: unexpected token str");
    return tok->next;
}

bool equal(t_token *tok, t_token_kind kind, char *str) {
    if (tok->kind != kind)
        return false;
    if (str != NULL
        && (tok->len != ft_strlen(str) || ft_strncmp(tok->str, str, tok->len) != 0))
        return false;
    return true;
}
