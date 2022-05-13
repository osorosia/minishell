#include "../minishell.h"

void expander(t_node *node) {
    expand_var(node);
    // debug_expander(node, "expand_var");

    split_space(node);
    // debug_expander(node, "split_space");

    delete_quote(node);
    // debug_expander(node, "delete_quote");

    generate_pathname(node);
    // debug_expander(node, "generate_pathname");
}

void expander_for_debug(t_node *node) {
    expand_var_for_debug(node);
    debug_expander(node, "expand_var");

    split_space_for_debug(node);
    debug_expander(node, "split_space");

    delete_quote_for_debug(node);
    debug_expander(node, "delete_quote");

    generate_pathname_for_debug(node);
    debug_expander(node, "generate_pathname");
}
