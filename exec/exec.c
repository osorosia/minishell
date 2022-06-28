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

void exec_builtin(t_node *node) {
    t_cmd *cmd = node->cmd;

    int (*builtin_fn[])(t_word *) = {
        exec_echo, exec_cd, exec_pwd, exec_export, exec_unset, exec_env, exec_exit, NULL
    };
    char *kw[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

    long i = 0;
    while (kw[i]) {
        if (strcmp(kw[i], cmd->word->str) == 0) {
            g_shell->sts = builtin_fn[i](cmd->word);
            break;
        }
        i++;
    }
    if (kw[i] == NULL) {
        error("no match builtin");
    }
}

bool set_redir_in(t_redir *redir_in) {
    if (redir_in == NULL)
        return true;

    if (redir_in->kind == RD_IN) {
        int fd = open(redir_in->str, O_RDONLY);
        if (fd < 0) {
            int eno = errno;
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(redir_in->str, 2);
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(eno), 2);
            return false;
        }
        dup2(fd, 0);
        close(fd);
    } else if (redir_in->kind == RD_HEREDOC) {
        if (redir_in->fd >= 0)
            dup2(redir_in->fd, 0);
        else
            error("error: redir_in: heredoc");
    } else {
        error("error: set_redir_in()");
    }

    return set_redir_in(redir_in->next);
}

bool set_redir_out(t_redir *redir_out) {
    if (redir_out == NULL)
        return true;

    if (redir_out->kind == RD_OUT) {
        int fd = open(redir_out->str, (O_WRONLY | O_CREAT | O_TRUNC), 0664);
        if (fd < 0) {
            int eno = errno;
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(redir_out->str, 2);
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(eno), 2);
            return false;
        }
        dup2(fd, 1);
        close(fd);
    } else if (redir_out->kind == RD_APPEND) {
        int fd = open(redir_out->str, (O_WRONLY | O_CREAT | O_APPEND), 0664);
        if (fd < 0) {
            int eno = errno;
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(redir_out->str, 2);
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(eno), 2);
            return false;
        }
        dup2(fd, 1);
        close(fd);
    } else {
        error("error: set_redir_out()");
    }

    return set_redir_out(redir_out->next);
}

bool is_directory(char *pathname) {
    struct stat st;
    
    if (stat(pathname, &st) != 0)
        return false;
    return S_ISDIR(st.st_mode);
}

void exec_cmd(t_node *node) {
    if (g_shell->interrupt)
        return;
    
    t_cmd *cmd = node->cmd;

    // redir in
    // redir out
    if ( !set_redir_in(cmd->redir_in)
        || !set_redir_out(cmd->redir_out))
    {
        g_shell->sts = 1;
        dup2(g_shell->stdout, 1);
        dup2(g_shell->stdin, 0);
        return;
    }

    if (cmd->word == NULL) {
        dup2(g_shell->stdout, 1);
        dup2(g_shell->stdin, 0);
        g_shell->sts = 0;
        return;
    }

    if (cmd->is_builtin) {
        exec_builtin(node);
    }
    else {
        int pid = fork();

        if (pid == 0) {
            if (cmd->pathname == NULL) {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(cmd->word->str, 2);
                ft_putstr_fd(": command not found\n", 2);
                exit(127);
            }
            if (is_directory(cmd->pathname)) {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(cmd->pathname, 2);
                ft_putstr_fd(": is a directory\n", 2);
                exit(126);
            }
            char **cmd_argv = create_argv(cmd->word);
            char **cmd_envp = create_envp();
            execve(cmd->pathname, cmd_argv, cmd_envp);
            int eno = errno;
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd->pathname, 2);
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(eno), 2);
            free(cmd_argv);
            free_envp(cmd_envp);
            if (eno == ENOENT)
                exit(127);
            exit(126);
        }
        int sts = 0;
        waitpid(pid, &sts, 0);
        g_shell->sts = WEXITSTATUS(sts);
    }

    dup2(g_shell->stdout, 1);
    dup2(g_shell->stdin, 0);
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
