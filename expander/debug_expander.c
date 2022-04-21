#include "../minishell.h"

void debug_word_ex(t_word *word, int indent) {
    while (word) {
        fprintf(stderr, "'%s' ", word->str);
        word = word->next;
    }
}

void debug_redir_ex(t_redir *redir, int indent) {
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

void debug_expander_rec(t_node *node, int indent) {
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
        
        debug_expander_rec(node->lhs, indent + INDENT);
        debug_expander_rec(node->rhs, indent);
    }

    if (node->kind == ND_PIPE) {
        debug_expander_rec(node->lhs, indent);
        
        print_indent(indent);
        fprintf(stderr, "pipe:\n");
        debug_expander_rec(node->rhs, indent + INDENT);
    }

    if (node->kind == ND_CMD) {
        print_indent(indent);
        fprintf(stderr, "cmd: ");

        debug_word_ex(node->cmd->word, indent);    
        debug_redir_ex(node->cmd->redir_in, indent);
        debug_redir_ex(node->cmd->redir_out, indent);

        fprintf(stderr, "\n");

        indent += INDENT;
        if (node->cmd->pathname) {
            print_indent(indent);
            fprintf(stderr, "pathname: %s\n", node->cmd->pathname);
        }
    }
}


void debug_expander(t_node *node, char *name) {
    printf("%s {\n", name);
    debug_expander_rec(node, INDENT);
    printf("}\n\n");
}
