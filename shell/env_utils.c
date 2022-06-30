#include "../minishell.h"

char *create_env_name(char *str) {
    char *name;
    char *eq;

    eq = ft_strchr(str, '=');
    if (eq == NULL)
        name = ft_xstrdup(str);
    else
        name = ft_xstrndup(str, eq - str);
    return name;
}

char *create_env_body(char *str) {
    char *body;
    char *eq;

    eq = ft_strchr(str, '=');
    if (eq == NULL)
        return NULL;
    body = ft_xstrdup(eq + 1);
    return body;
}

char *create_env_name_plus(char *str) {
    char *name;
    char *eq;

    eq = ft_strnstr(str, "+=", ft_strlen(str));
    if (eq == NULL)
        name = ft_xstrdup(str);
    else
        name = ft_xstrndup(str, eq - str);
    return name;
}

char *create_env_body_plus(char *str) {
    char *body;
    char *eq;

    eq = ft_strnstr(str, "+=", ft_strlen(str));
    if (eq == NULL)
        return NULL;
    body = ft_xstrdup(eq + 2);
    return body;
}
