#include"../inc/ush.h"

char *update_path (const char *line) {
    char *fix = strdup(line);
    char **pathes = mx_strsplit(fix, '/');
    char *temp = strdup(cur_path);
    int shift = 0;
    if (!(*pathes)) {
        pathes = malloc(sizeof(char*) * 2);
        pathes[0] = strdup(fix);
        pathes[1] = NULL;
    }
    while (*pathes)
    {
        if (strcmp(*pathes, "..") == 0) {
            mx_str_reverse(temp);
            int ind = mx_get_char_index(temp, '/');
            mx_str_reverse(temp);
            temp = strndup(temp, strlen(temp) - ind - 1);
        }
        else if (strcmp(*pathes, ".") == 0) continue;
        else {
            temp = mx_strjoin(temp, "/");
            temp = mx_strjoin(temp, *pathes);
        }
        //printf("%s\n", temp);
        pathes++; shift++;
    }
    mx_strdel(&fix);
    pathes -= sizeof(char) * shift;
    mx_del_strarr(&pathes);
    return temp;
    
    
}


