#include "../minishell.h"

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
        fprintf(stderr, "%s'%s' ", kw[redir->kind], redir->str);
        redir = redir->next;
    }
}

void debug_parser_rec(t_node *node, int indent) {
    if (!node)
        return;
    
    if (node->kind == ND_STMT || node->kind == ND_AND || node->kind == ND_OR) {
        print_indent(indent);
        if (node->kind == ND_STMT)
            fprintf(stderr, "stmt:\n");
        if (node->kind == ND_AND)
            fprintf(stderr, "&&:\n");
        if (node->kind == ND_OR)
            fprintf(stderr, "||:\n");
        
        debug_parser_rec(node->lhs, indent + INDENT);
        debug_parser_rec(node->rhs, indent);
    }

    if (node->kind == ND_PIPE) {
        debug_parser_rec(node->lhs, indent);
        
        print_indent(indent);
        fprintf(stderr, "pipe:\n");
        debug_parser_rec(node->rhs, indent + INDENT);
    }

    if (node->kind == ND_CMD) {
        print_indent(indent);
        fprintf(stderr, "cmd: ");

        // word
        debug_word(node->cmd->word, indent);    
        // redirect in
        debug_redir(node->cmd->redir_in, indent);
        // redirect out
        debug_redir(node->cmd->redir_out, indent);

        fprintf(stderr, "\n");
    }
}

void debug_parser(t_node *node) {
    fprintf(stderr, "parser {\n");
    debug_parser_rec(node, INDENT);
    fprintf(stderr, "}\n\n");
}
