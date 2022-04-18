#include "../libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define INDENT 15

bool ok = true;

#define CASE(s) printf("\n%-*s:", INDENT, s)

void KO() {printf("x"); ok=false;}
void OK() {printf("o");}

void assert_bool(bool expected, bool actual) {
    if (actual == expected) OK();
    else KO();
}
void assert_size_t(size_t expected, size_t actual) {
    if (actual == expected) OK();
    else KO();
}
void assert_char_p(char *expected, char *actual) {
    if (!strcmp(expected, actual)) OK();
    else KO();
}

void ft_isnumber_test() {
    CASE("ft_isnumber");
    assert_bool(true, ft_isnumber("12"));
    assert_bool(true, ft_isnumber("-12"));
    assert_bool(true, ft_isnumber("+12"));
    assert_bool(true, ft_isnumber("0"));
    assert_bool(true, ft_isnumber("+0"));
    assert_bool(true, ft_isnumber("-0"));
    assert_bool(true, ft_isnumber("012"));
    assert_bool(true, ft_isnumber("0012"));
    assert_bool(true, ft_isnumber("-0012"));
    assert_bool(true, ft_isnumber("+0012"));
    assert_bool(false, ft_isnumber("--122"));
    assert_bool(false, ft_isnumber("++122"));
    assert_bool(false, ft_isnumber("-"));
    assert_bool(false, ft_isnumber("+"));
}

void ft_numlen_test() {
    CASE("ft_numlen");
    assert_size_t(1, ft_numlen(0));
    assert_size_t(1, ft_numlen(1));
    assert_size_t(2, ft_numlen(10));
    assert_size_t(2, ft_numlen(-1));
    assert_size_t(3, ft_numlen(-10));
    assert_size_t(ft_strlen("2147483647"), ft_numlen(INT_MAX));
    assert_size_t(ft_strlen("-2147483648"), ft_numlen(INT_MIN));
    assert_size_t(ft_strlen("9223372036854775807"), ft_numlen(LLONG_MAX));
    assert_size_t(ft_strlen("-9223372036854775808"), ft_numlen(LLONG_MIN));
}

void ft_numlen_base_test() {
    CASE("ft_numlen_base");
    assert_size_t(1, ft_numlen_base(0, 10));
    assert_size_t(1, ft_numlen_base(1, 10));
    assert_size_t(2, ft_numlen_base(10, 10));
    assert_size_t(2, ft_numlen_base(-1, 10));
    assert_size_t(3, ft_numlen_base(-10, 10));
    assert_size_t(ft_strlen("2147483647"), ft_numlen_base(INT_MAX, 10));
    assert_size_t(ft_strlen("-2147483648"), ft_numlen_base(INT_MIN, 10));
    assert_size_t(ft_strlen("9223372036854775807"), ft_numlen_base(LLONG_MAX, 10));
    assert_size_t(ft_strlen("-9223372036854775808"), ft_numlen_base(LLONG_MIN, 10));
}

void ft_numlen_u_test() {
    CASE("ft_numlen_u");
    assert_size_t(1, ft_numlen_u(0));
    assert_size_t(1, ft_numlen_u(1));
    assert_size_t(2, ft_numlen_u(10));
    assert_size_t(ft_strlen("2147483647"), ft_numlen_u(INT_MAX));
    assert_size_t(ft_strlen("2147483648"), ft_numlen_u((size_t)INT_MAX + 1));
    assert_size_t(ft_strlen("4294967295"), ft_numlen_u(UINT_MAX));
    assert_size_t(ft_strlen("4294967296"), ft_numlen_u((size_t)UINT_MAX + 1));
    assert_size_t(ft_strlen("9223372036854775807"), ft_numlen_u(LLONG_MAX));
    assert_size_t(ft_strlen("9223372036854775808"), ft_numlen_u((unsigned long long)LLONG_MAX + 1));
    assert_size_t(ft_strlen("18446744073709551615"), ft_numlen_u(ULLONG_MAX));
}

void ft_numlen_u_base_test() {
    CASE("ft_numlen_u_base");
    assert_size_t(1, ft_numlen_u_base(0, 10));
    assert_size_t(1, ft_numlen_u_base(1, 10));
    assert_size_t(2, ft_numlen_u_base(10, 10));
    assert_size_t(ft_strlen("2147483647"), ft_numlen_u_base(INT_MAX, 10));
    assert_size_t(ft_strlen("2147483648"), ft_numlen_u_base((size_t)INT_MAX + 1, 10));
    assert_size_t(ft_strlen("4294967295"), ft_numlen_u_base(UINT_MAX, 10));
    assert_size_t(ft_strlen("4294967296"), ft_numlen_u_base((size_t)UINT_MAX + 1, 10));
    assert_size_t(ft_strlen("9223372036854775807"), ft_numlen_u_base(LLONG_MAX, 10));
    assert_size_t(ft_strlen("9223372036854775808"), ft_numlen_u_base((unsigned long long)LLONG_MAX + 1, 10));
    assert_size_t(ft_strlen("18446744073709551615"), ft_numlen_u_base(ULLONG_MAX, 10));
}

void get_next_line_test() {
    CASE("get_next_line");
    int fd = open("test.txt", O_RDONLY);
    char *expected[] = {
        "aaaaaaaa\n","bbbbbbb\n","cccccc\n","ddddd\n","eeee\n","fff\n","gg\n","h\n",
    };
    for (int i = 0; i < sizeof(expected)/sizeof(expected[0]); i++) {
        char *line = get_next_line(fd);
        assert_char_p(expected[i], line);
        if (line == NULL) break;
        free(line);
    }
}

void result() {
    if (ok) printf("\ntest OK!");
    else printf("\ntest KO");
}

int main() {
    printf("------start------");
    ft_isnumber_test();
    ft_numlen_test();
    ft_numlen_base_test();
    ft_numlen_u_test();
    ft_numlen_u_base_test();
    get_next_line_test();
    result();
    printf("\n-------end-------\n");
}
