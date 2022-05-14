#include "../minishell.h"

char *create_env_name(char *str) {
    char *name;
    char *eq;

    eq = ft_strchr(str, '=');
    if (eq == NULL)
        name = ft_strdup(str);
    else
        name = ft_strndup(str, eq - str);
    if (name == NULL)
        error("malloc error");
    return name;
}

char *create_env_body(char *str) {
    char *body;
    char *eq;

    eq = ft_strchr(str, '=');
    if (eq == NULL)
        return NULL;
    body = ft_strdup(eq + 1);
    if (body == NULL)
        error("malloc error");
    return body;
}

char *create_env_name_plus(char *str) {
    char *name;
    char *eq;

    eq = ft_strnstr(str, "+=", ft_strlen(str));
    if (eq == NULL)
        name = ft_strdup(str);
    else
        name = ft_strndup(str, eq - str);
    if (name == NULL)
        error("malloc error");
    return name;
}

char *create_env_body_plus(char *str) {
    char *body;
    char *eq;

    eq = ft_strnstr(str, "+=", ft_strlen(str));
    if (eq == NULL)
        return NULL;
    body = ft_strdup(eq + 2);
    if (body == NULL)
        error("malloc error");
    return body;
}
