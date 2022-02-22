#include "../inc/ush.h"

int get_input(char* str) {
    char* buf;
    buf = readline("u$h> ");  
    if(!buf) {
        // if(read(0, buf, 1) == 0)
        //     mx_printchar('\n');
        //mx_printstr("\n\n[PROCESS FINISHED]\n\n");
        exit(0);
    }
    if (strlen(buf) != 0) {
        add_history(buf);
        mx_strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}
