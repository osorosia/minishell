#include "../minishell.h"

char **get_argv(t_word *word) {
    char **argv;
    long len;
    t_word *now;

    len = 0;
    now = word;
    while (now) {
        len++;
        now = now->next;
    }

    argv = ft_calloc(len + 1, sizeof(char *));
    long i = 0;
    while (word) {
        argv[i] = word->str;
        i++;
        word = word->next;
    }
    return argv;
}

void exec_cmd(t_node *node) {
    t_cmd *cmd = node->cmd;

    if (cmd->is_builtin) {
        // TODO
    }
    else {
        int pid = fork();

        if (pid == 0) {
            execve(cmd->pathname, get_argv(cmd->word), NULL);
            exit(127);
        }
        wait(&(g_shell->sts));
        g_shell->sts = WEXITSTATUS(g_shell->sts);
    }
}

void exec_no_pipe(t_node *pipe_node) {
    exec_cmd(pipe_node->rhs);
}

void exec_pipe(t_node *pipe_node) {
    int fd[2];

    if (pipe_node->lhs == NULL) {
        exec_cmd(pipe_node->rhs);
        return;
    }
    
    pipe(fd);
    int pid = fork();

    if (pid == 0) {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        exec_pipe(pipe_node->lhs);
    }
    else {
        dup2(fd[0], 0);
        close(fd[1]);
        close(fd[0]);
        exec_cmd(pipe_node->rhs);
    }
    exit(g_shell->sts);
}

void exec_stmt(t_node *stmt_node) {
    t_node *pipe_node;

    if (stmt_node->kind == ND_OR && g_shell->sts == 0)
        return;
    if (stmt_node->kind == ND_AND && g_shell->sts != 0)
        return;
    pipe_node = stmt_node->lhs;
    if (pipe_node->lhs == NULL)
        exec_no_pipe(pipe_node);
    else {
        int pid = fork();
        if (pid == 0)
            exec_pipe(pipe_node);
        wait(&(g_shell->sts));
        g_shell->sts = WEXITSTATUS(g_shell->sts);
    }
}

void exec(t_node *node) {
    t_node *stmt_node;

    stmt_node = node;
    while (stmt_node) {
        exec_stmt(stmt_node);
        stmt_node = stmt_node->rhs;
    }
}