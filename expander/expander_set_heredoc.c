#include "../minishell.h"

void set_heredoc(t_redir *redir) {
    if (redir == NULL)
        return;
    if (redir->kind == RD_HEREDOC) {
        ft_putstr_fd("heredoc: ", 2);
        ft_putstr_fd(redir->str, 2);
        ft_putstr_fd("\n", 2);
        
        int fd[2];
        pipe(fd);
        redir->fd = fd[0];
        char *line;
        while (1) {
            line = get_next_line(0);
            if (line == NULL) {
                ft_putstr_fd("warning: here-document\n", 2);
                break;
            }
            if (ft_strlen(line) > 1 && ft_strncmp(line, redir->str, ft_strlen(line) - 1) == 0) {
                free(line);
                break;
            }
            write(fd[1], line, ft_strlen(line));
            free(line);
        }
        close(fd[1]);
    }
    set_heredoc(redir->next);
}

void expander_set_heredoc(t_node *node) {
    if (node == NULL)
        return;
    if (node->kind == ND_CMD) {
        delete_quote_in_heredoc(node->cmd->redir_in);
        set_heredoc(node->cmd->redir_in);
    } else {
        expander_set_heredoc(node->lhs);
        expander_set_heredoc(node->rhs);
    }
}
