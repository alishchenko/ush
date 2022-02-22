#include "../inc/ush.h"

bool comp (char *s1, char *s2) {
    while (*s1 != '\0' && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *s1 < *s2;
}
extern char **environ;
static int size_of_environ() {
    int i;
    for(i = 0; environ[i] != NULL; i++) {}
    return i;
}

void mx_export (char** parsed) {
    parsed++;
    if (*parsed) {
        while (*parsed) {            
            char *name = mx_strndup(*parsed, mx_get_char_index(*parsed, '='));
            char *value = mx_strdup(mx_strchr(*parsed, '=') == 0 ? NULL : mx_strchr(*parsed, '='));
            if(value) {
                value++;
                setenv(name, value, 1);
                value--;
                mx_strdel(&value);
            }
            else {
                name = mx_strdup(*parsed);
                setenv(name, "\'\'", 1);
            }
            char *temp = environ[size_of_environ() - 1];
            environ[size_of_environ() - 1] = environ[size_of_environ() - 2];
            environ[size_of_environ() - 2] = temp;
            mx_strdel(&name);
            parsed++;
        }
    }
    else {
        int e_size = 0;
        for (int i = 0; environ[i] != NULL; i++) {
            e_size++;
        }
        char **e = malloc(e_size * sizeof(char*));
        for (int i = 0; environ[i] != NULL; i++) {
            e[i] = mx_strdup(environ[i]);
        }
        e[e_size] = NULL;
        //mx_bubble_sort(e, e_size, comp);
        for (int i = 0; e[i] != NULL; i++) {
            mx_printstr(e[i]);
            mx_printchar('\n');
        }
        //mx_del_strarr(&e);
    }
}

