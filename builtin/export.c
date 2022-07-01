#include "../minishell.h"


void show_envs() {
    t_env *env = g_shell->env;
    while (env) {
        if (env->body)
            ft_printf("declare -x %s=\"%s\"\n", env->name, env->body);
        else
            ft_printf("declare -x %s\n", env->name);
        env = env->next;
    }
}

bool validate_name(char *str) {
    if (ft_strncmp(str, "+=", 2) == 0 || str[0] == '=')
        return false;
    long i = 0;
    while (str[i] && str[i] != '=' && (str[i] != '+' || str[i + 1] != '=')) {
        if (i == 0 && ft_isdigit(str[i]))
            return false;
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return false;
        i++;
    }
    return true;
}

int exec_export(t_word *word) {
    int ret = 0;

    if (word->next == NULL) {
        show_envs();
        return 0;
    }
    word = word->next;
    while (word) {
        if (!validate_name(word->str)) {
            ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n", word->str);
            ret = 1;
        } else if (ft_strnstr(word->str, "+=", ft_strlen(word->str))) {
            add_env_plus(word->str);
        } else {
            add_env(word->str);
        }
        word = word->next;
    }
    return ret;
}
