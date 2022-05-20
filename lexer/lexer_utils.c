#include "../minishell.h"

t_token *skip(t_token *tok, t_token_kind kind, char *str) {
    if (tok->kind != kind) {
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putnstr_fd(tok->str, tok->len, 2);
        ft_putstr_fd("'\n", 2);
        exit(1);
    }
    if (str != NULL
        && (tok->len != ft_strlen(str) || ft_strncmp(tok->str, str, tok->len) != 0))
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putnstr_fd(tok->str, tok->len, 2);
        ft_putstr_fd("'\n", 2);
        exit(1);
    }
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
