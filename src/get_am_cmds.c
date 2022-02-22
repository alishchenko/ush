#include "../inc/ush.h"

int get_amount_cmds(char **input_str) {
    int am = 0;
    for(int i = 0; input_str[i] != NULL; i++) {
        if(mx_strcmp(input_str[i], ";") == 0) {
            am++;
        }   
    }
    return am + 1;
}
