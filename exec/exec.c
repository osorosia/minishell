#include "../minishell.h"

void exec_cmd(t_node *node);
void exec_bracket(t_node *pipe_node);
void exec_no_pipe(t_node *pipe_node);
void exec_pipe(t_node *pipe_node);
void exec_stmt(t_node *stmt_node);

char **create_argv(t_word *word) {
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
            char **cmd_argv = create_argv(cmd->word);
            execve(cmd->pathname, cmd_argv, NULL);
            free(cmd_argv);
            exit(127);
        }
        int sts = 0;
        waitpid(pid, &sts, 0);
        g_shell->sts = WEXITSTATUS(sts);
    }
}

void exec_bracket(t_node *bracket_node) {
    if (bracket_node->kind == ND_BRACKET) {
        int pid = fork();
        if (pid == 0) {
            exec_stmt(bracket_node->lhs);
            exit(g_shell->sts);
        }
        int sts = 0;
        waitpid(pid, &sts, 0);
        g_shell->sts = WEXITSTATUS(sts);
    }
    else
        exec_cmd(bracket_node);
}

void exec_no_pipe(t_node *pipe_node) {
    exec_bracket(pipe_node->rhs);
}

void exec_pipes(t_node *pipe_node) {
    if (pipe_node == NULL)
        return;

    int fd[2];
    pipe(fd);
    
    int pid = fork();
    if (pid == 0) {
        if (pipe_node->lhs)
            dup2(fd[0], 0);
        close(fd[1]);
        close(fd[0]);
        exec_bracket(pipe_node->rhs);
        exit(g_shell->sts);
    }
    else {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        exec_pipes(pipe_node->lhs);
    }
    int sts = 0;
    waitpid(pid, &sts, 0);
    g_shell->sts = WEXITSTATUS(sts);
}

void exec_pipe(t_node *pipe_node) {
    expander(pipe_node);
    if (pipe_node->lhs == NULL)
        exec_no_pipe(pipe_node);
    else {
        int pid = fork();
        if (pid == 0) {
            exec_pipes(pipe_node);
            exit(g_shell->sts);
        }
        int sts = 0;
        waitpid(pid, &sts, 0);
        g_shell->sts = WEXITSTATUS(sts);
    }
}

void exec_stmt(t_node *stmt_node) {
    if (stmt_node == NULL)
        return;
    if (stmt_node->kind == ND_OR && g_shell->sts == 0) {
        exec_stmt(stmt_node->rhs);
        return;
    }
    if (stmt_node->kind == ND_AND && g_shell->sts != 0) {
        exec_stmt(stmt_node->rhs);
        return;
    }
    t_node *pipe_node = stmt_node->lhs;
    exec_pipe(pipe_node);
    exec_stmt(stmt_node->rhs);
}

void exec(t_node *node) {
    exec_stmt(node);
}
