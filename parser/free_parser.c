#include "../minishell.h"

void free_word(t_word *word) {
    if (!word)
        return;
    free_word(word->next);
    free(word->str);
    free(word);
}
void free_redir(t_redir *redir) {
    if (!redir)
        return;
    free_redir(redir->next);
    free(redir->str);
    free(redir);
}

void free_parser(t_node *node) {
    if (!node)
        return;

    if (node->kind != ND_CMD) {
        free_parser(node->lhs);
        free_parser(node->rhs);
    }
    else {
        free_word(node->cmd->word);
        free_redir(node->cmd->redir_in);
        free_redir(node->cmd->redir_out);
        free(node->cmd->pathname);
        free(node->cmd);
    }
    free(node);
}
