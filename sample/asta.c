#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

void sort_ls(char **arr) {
    for (int i = 0; arr[i]; i++) {
        for (int j = 0; arr[j]; j++) {
            if (strcmp(arr[i], arr[j]) < 0) {
                char *tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

bool ok(char *pattern, char *str, long i, long j) {
    // 隠しファイルかどうか
    if (i == 0 && j == 0) {
        if (pattern[i] != '.' && str[j] == '.')
            return false;
    }

    if (str[j] == '\0') {
        while (pattern[i] != '\0') {
            if (pattern[i] != '*')
                return false;
            i++;
        }
        return true;
    }

    if (pattern[i] == '*') {
        if (ok(pattern, str, i, j + 1))
            return true;
        if (ok(pattern, str, i + 1, j))
            return true;
    } else if (pattern[i] == str[j]) {
        if (ok(pattern, str, i + 1, j + 1))
            return true;
    }

    return false;
}

char **add_back(char **arr, char *str) {
    long len = 0;
    if (arr != NULL) {
        while (arr[len])
            len++;
    }

    char **new = calloc(len + 2, sizeof(char *));
    long i = 0;
    while (arr && arr[i]) {
        new[i] = arr[i];
        i++;
    }
    new[i] = strdup(str);
    free(arr);
    return new;
}

char **asta(char *str) {
    char **arr = NULL;
    
    DIR *dir = opendir(".");
    while (true) {
        struct dirent *ent = readdir(dir);
        if (ent == NULL)
            break;
        if (ok(str, ent->d_name, 0, 0)) {
            arr = add_back(arr, ent->d_name);
        }
    }
    closedir(dir);

    if (arr != NULL) {
        sort_ls(arr);
        free(str);
    } else {
        arr = calloc(2, sizeof(char *));
        arr[0] = str;
    }
    return arr;
}

int main(int c, char **v, char **p) {
    char **arr = asta(strdup("*"));

    for (int i = 0; arr[i]; i++) {
        printf("%s\n", arr[i]);
    }
}

