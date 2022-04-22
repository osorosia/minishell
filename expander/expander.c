#include "../minishell.h"

void expander(t_node *node) {
    expand_var(node);
    //debug_expander(node, "expand_var");

    generate_pathname(node);
    //debug_expander(node, "generate_pathname");
}
