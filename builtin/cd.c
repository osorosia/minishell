#include "../minishell.h"

int cd_home() {
    char *home = get_env_body("HOME");
    if (home == NULL) {
        ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        return 1;
    }
    int ret = chdir(home);
    if (ret != 0) {
        int eno = errno;
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(home, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(eno), 2);
        return 1;
    }

    char *pwd_body = get_env_body("PWD");
    if (pwd_body) {
        char *str = ft_strjoin("OLDPWD=", pwd_body);
        add_env(str);
        free(str);
    }

    char path[PATH_MAX + 1];
    getcwd(path, sizeof(path));
    {
        char *str = ft_strjoin("PWD=", path);
        add_env(str);
        free(str);
    }

    return 0;
}

int exec_cd(t_word *word) {
    // no args
    if (word->next == NULL) {
        return cd_home();        
    }

    // if (word->next->next != NULL) {
    //     ft_putstr_fd("cd: too many arguments\n", 2);
    //     return 1;
    // }

    int ret = chdir(word->next->str);
    if (ret != 0) {
        int eno = errno;
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(word->next->str, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(eno), 2);
        return 1;
    }

    char *pwd_body = get_env_body("PWD");
    if (pwd_body) {
        char *str = ft_strjoin("OLDPWD=", pwd_body);
        add_env(str);
        free(str);
    }

    char path[PATH_MAX + 1];
    getcwd(path, sizeof(path));
    {
        char *str = ft_strjoin("PWD=", path);
        add_env(str);
        free(str);
    }

    return 0;
}
