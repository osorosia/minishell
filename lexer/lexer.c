#include "../minishell.h"

void _add_new_token(t_token *tok, t_token_kind kind, char *str, long len) {
    t_token *new;
    
    while (tok->next)
        tok = tok->next;
    new = ft_xcalloc(1, sizeof(t_token));
    new->kind = kind;
    new->str = str;
    new->len = len;
    tok->next = new;
}

long _get_operator_len(char *p) {
    const char *kw[] = {"||", "&&", "<<", ">>", "<", ">", "|", ";", "(", ")", NULL};   
    long i;

    i = 0;
    while (kw[i]) {
        if (starts_with(p, kw[i]))
            return ft_strlen(kw[i]);
        i++;
    }
    return 0;
}

long _get_quote_len(char *p, char quote) {
    long len;

    if (p[0] != quote)
        error("lexer error: expected quote (start)");
    len = 1;
    while (p[len] != '\0' && p[len] != quote)
        len++;
    if (p[len] == '\0')
        error("lexer error: expected quote (end)");
    return len + 1;
}

long _get_word_len(char *p) {
    long len;

    len = 0;
    while (p[len] != '\0' && !ft_strchr("|<>;&() ", p[len])) {
        if (p[len] == '"' || p[len] == '\'')
            len += _get_quote_len(&(p[len]), p[len]);
        else
            len++;
    }
    return len;
}

t_token *lexer(char *p) {
    t_token tok;
    long len;

    tok.next = NULL;
    while (*p) {
        // space
        if (*p == ' ')
            p++;
        // operator
        else if ((len = _get_operator_len(p)) > 0) {
            _add_new_token(&tok, TK_OP, p, len);
            p += len;
        }
        // word
        else if ((len = _get_word_len(p)) > 0) {
            _add_new_token(&tok, TK_WORD, p, len);
            p += len;
        }
        else
            error("lexer error: unexpected character");
    }
    _add_new_token(&tok, TK_EOF, p, 0);
    return tok.next;
}
