#include "../inc/libmx.h"

void swap_strings(char **str1, char **str2) {
    char *temp = mx_strdup(*str1);
    mx_strdel(str1);
    *str1 = mx_strdup(*str2);
    mx_strdel(str2);
    *str2 = mx_strdup(temp);
    mx_strdel(&temp);
}
