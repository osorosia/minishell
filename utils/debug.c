#include "../minishell.h"

void print_indent(int indent) {
    fprintf(stderr, "%*s", indent, "");
}
