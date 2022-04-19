#include "../minishell.h"

void debug_parser(t_node *node);
void debug_stmt(t_node *node, int indent);
void debug_pipe(t_node *node, int indent);
void debug_cmd(t_node *node, int indent);
void debug_word(t_word *word, int indent);
void debug_redir(t_redir *redir, int indent);

void debug_parser(t_node *node) {
    fprintf(stderr, "parser {\n");
    debug_stmt(node, INDENT);
    fprintf(stderr, "}\n\n");
}

void debug_stmt(t_node *node, int indent) {
    while (node) {
        if (node->kind != ND_STMT && node->kind != ND_AND && node->kind != ND_OR)
            error("debug error");

        print_indent(indent);
        char *op = node->kind == ND_AND ? "&& " :
                   node->kind == ND_OR ? "|| " :
                   "";
        fprintf(stderr, "%sstmt:\n", op);

        debug_pipe(node->lhs, indent + INDENT);

        node = node->rhs;
    }
}

void debug_pipe(t_node *node, int indent) {
    if (!node)
        return;
    if (node->kind != ND_PIPE)
        error("debug error");

    debug_pipe(node->lhs, indent);

    print_indent(indent);
    fprintf(stderr, "pipe:\n");

    debug_cmd(node->rhs, indent + INDENT);
}

void debug_cmd(t_node *node, int indent) {
    if (node->kind != ND_CMD)
        error("debug error");

    print_indent(indent);
    fprintf(stderr, "cmd:\n");
    indent += INDENT;

    t_cmd *cmd = node->cmd;

    // word
    print_indent(indent);
    fprintf(stderr, "word: ");
    debug_word(cmd->word, indent);
    fprintf(stderr, "\n");
    
    // redirect in
    print_indent(indent);
    fprintf(stderr, "in: ");
    debug_redir(cmd->redir_in, indent);
    fprintf(stderr, "\n");

    // redirect out
    print_indent(indent);
    fprintf(stderr, "out: ");
    debug_redir(cmd->redir_out, indent);
    fprintf(stderr, "\n");

    indent -= INDENT;
}

void debug_word(t_word *word, int indent) {
    while (word) {
        fprintf(stderr, "'%s' ", word->str);
        word = word->next;
    }
}

void debug_redir(t_redir *redir, int indent) {
    const char *kw[] = {
        ">",
        "<",
        ">>",
        "<<",
    };
    
    while (redir) {
        fprintf(stderr, "%s '%s'  ", kw[redir->kind], redir->str);
        redir = redir->next;
    }
}
