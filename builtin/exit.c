#include "../minishell.h"

bool is_number(char *str) {
    if (str[0] == '\0')
        return false;

    long i = 0;
    if (str[i] == '-' || str[i] == '+') {
        i++;
        if (!ft_isdigit(str[i]))
            return false;
    }
    while (str[i]) {
        if (!ft_isdigit(str[i]))
            return false;
        i++;
    }
    return true;
}

bool check_overflow(char *str) {
    unsigned long num = 0;
    bool minus = false;

    long i = 0;
    if (str[i] == '-' || str[i] == '+') {
        minus = (str[i] == '-');
        i++;
    }
    while (str[i]) {
        if ((num * 10 + str[i] - '0') / 10 != num) {
            return false;
        }
        num = num * 10 + str[i] - '0';
        if (num > (unsigned long)LONG_MAX + minus)
            return false;
        i++;
    }
    return true;
}

int _atoi(char *str) {
    long sign = 1;
    long num = 0;

    long i = 0;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i]) {
        num = 10 * num + str[i] - '0';
        i++;
    }
    return sign * num;
}

int exec_exit(t_word *word) {
    if (word->next == NULL)
        exit(g_shell->sts);

    // numeric argument required
    if (!is_number(word->next->str)) {
        ft_putstr_fd("exit: numeric argument required\n", 2);
        exit(2);
    }

    if (!check_overflow(word->next->str)) {
        ft_putstr_fd("exit: numeric argument required\n", 2);
        exit(2);
    }

    // too many arguments
    if (word->next->next) {
        ft_putstr_fd("exit: too many arguments\n", 2);
        exit(1);
    }

    // ok
    exit(_atoi(word->next->str));
    return 0;
}
