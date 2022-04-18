#include "minishell.h"

int main(int argc, char **argv, char **envp) {
    while (true) {
        char *str = readline("minishell$ ");
        add_history(str);

        printf("%s\n", str);
    }
}
