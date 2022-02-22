#include "../inc/ush.h"

void mx_exit(char **parsed) {
    mx_strdel(&cur_path);
    mx_strdel(&prev_path);
    
    if(parsed[1] == NULL) 
        exit(0);
    else
        exit(mx_atoi(parsed[1]));
}
