#include "../minishell.h"

t_node *_new_node_stmt(t_node_kind kind, t_node *pipe_cmd_node) {
    t_node *node;

    node = ft_calloc(1, sizeof(t_node));
    if (node == NULL)
        error("malloc error");
    node->kind = kind;
    node->lhs = pipe_cmd_node;
    return node;
}

void _add_node_stmt(t_node *node, t_node_kind kind, t_node *pipe_cmd_node) {
    while (node->rhs)
        node = node->rhs;
    node->rhs = _new_node_stmt(kind, pipe_cmd_node);;
}

t_node *_new_node_pipe(t_node *cmd_node) {
    t_node *node;

    node = ft_calloc(1, sizeof(t_node));
    if (node == NULL)
        error("malloc error");
    node->kind = ND_PIPE;
    node->rhs = cmd_node;
    return node;
}

t_node *_add_node_pipe(t_node *node, t_node *cmd_node) {
    t_node *new;
    
    new = _new_node_pipe(cmd_node);
    new->lhs = node;
    return new;
}

t_node *_new_node_cmd() {
    t_node *node;

    node = ft_calloc(1, sizeof(t_node));
    if (node == NULL)
        error("malloc error");
    node->cmd = ft_calloc(1, sizeof(t_cmd));
    if (node == NULL)
        error("malloc error");
    node->kind = ND_CMD;
    return node;
}

void *_add_word(t_cmd *cmd, char *str, long len) {
    t_word *word;
    t_word *now;

    word = ft_calloc(1, sizeof(t_word));
    if (word == NULL)
        error("malloc error");
    word->str = ft_strndup(str, len);
    if (word->str == NULL)
        error("malloc error");
    if (!cmd->word)
        cmd->word = word;
    else {
        now = cmd->word;
        while (now->next)
            now = now->next;
        now->next = word;
    }
}

void _add_redir_in(t_cmd *cmd, t_redir_kind kind, char *str, long len) {
    t_redir *redir;
    t_redir *now;
    
    redir = ft_calloc(1, sizeof(t_redir));
    if (redir == NULL)
        error("malloc error");
    redir->str = ft_strndup(str, len);
    if (redir->str == NULL)
        error("malloc error");
    redir->kind = kind;
    if (!cmd->redir_in)
        cmd->redir_in = redir;
    else {
        now = cmd->redir_in;
        if (now->next)
            now = now->next;
        now->next = redir;
    }
}

void _add_redir_out(t_cmd *cmd, t_redir_kind kind, char *str, long len) {
    t_redir *redir;
    t_redir *now;
    
    redir = ft_calloc(1, sizeof(t_redir));
    if (redir == NULL)
        error("malloc error");
    redir->str = ft_strndup(str, len);
    if (redir->str == NULL)
        error("malloc error");
    redir->kind = kind;
    if (!cmd->redir_out)
        cmd->redir_out = redir;
    else {
        now = cmd->redir_out;
        if (now->next)
            now = now->next;
        now->next = redir;
    }
}

t_node *parser(t_token *tok);
t_node *stmt(t_token **tok);
t_node *pipe_cmd(t_token **tok);
t_node *cmd(t_token **tok);

t_node *word(t_token **tok);
t_node *redir_in(t_token **tok);
t_node *redir_out(t_token **tok);

// parser = stmt ";"? EOF
t_node *parser(t_token *tok) {
    t_node *node;

    // stmt
    node = stmt(&tok);
    // ";"?
    if (equal(tok, TK_OP, ";"))
        tok = skip(tok, TK_OP, ";");
    // EOF
    tok = skip(tok, TK_EOF, NULL);
    return node;
}

// stmt = pipe ((";" | "||" | "&&") pipe)*
t_node *stmt(t_token **tok) {
    t_node *node;

    // pipe
    node = _new_node_stmt(ND_STMT, pipe_cmd(tok));
    // ((";" | "||" | "&&") pipe)*
    while (true) {
        if (equal(*tok, TK_OP, ";") && !equal((*tok)->next, TK_EOF, NULL)) {
            *tok = skip(*tok, TK_OP, ";");
            _add_node_stmt(node, ND_STMT, pipe_cmd(tok));
        }
        else if (equal(*tok, TK_OP, "||")) {
            *tok = skip(*tok, TK_OP, "||");
            _add_node_stmt(node, ND_OR, pipe_cmd(tok));
        }
        else if (equal(*tok, TK_OP, "&&")) {
            *tok = skip(*tok, TK_OP, "&&");
            _add_node_stmt(node, ND_AND, pipe_cmd(tok));
        }
        else
            return node;
    }
}

// pipe_cmd = cmd ("|" cmd)*
t_node *pipe_cmd(t_token **tok) {
    t_node *node;

    node = _new_node_pipe(cmd(tok));
    while (equal(*tok, TK_OP, "|")) {
        *tok = skip(*tok, TK_OP, "|");
        node = _add_node_pipe(node, cmd(tok));
    }
    return node;
}

// cmd = (word | redir_in | redir_out)*
t_node *cmd(t_token **tok) {
    t_node *node;

    node = _new_node_cmd();
    while (true) {
        if (equal(*tok, TK_WORD, NULL))
            _add_word(node->cmd, (*tok)->str, (*tok)->len);
        else if (equal(*tok, TK_OP, "<<")) {
            *tok = skip(*tok, TK_OP, "<<");
            _add_redir_in(node->cmd, RD_HEREDOC, (*tok)->str, (*tok)->len);
        }
        else if (equal(*tok, TK_OP, "<")) {
            *tok = skip(*tok, TK_OP, "<");
            _add_redir_in(node->cmd, RD_IN, (*tok)->str, (*tok)->len);
        }
        else if (equal(*tok, TK_OP, ">>")) {
            *tok = skip(*tok, TK_OP, ">>");
            _add_redir_out(node->cmd, RD_APPEND, (*tok)->str, (*tok)->len);
        }
        else if (equal(*tok, TK_OP, ">")) {
            *tok = skip(*tok, TK_OP, ">");
            _add_redir_out(node->cmd, RD_OUT, (*tok)->str, (*tok)->len);
        }
        else
            return node;
        *tok = skip(*tok, TK_WORD, NULL);
    }
}
