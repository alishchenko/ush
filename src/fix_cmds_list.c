#include "../inc/ush.h"

char **fix_command_list(char ***input_str, int *shift) {
    char **temp;
    int i = 0;
    for(i = 0; (*input_str)[i] != NULL; i++) {
        if(mx_strcmp((*input_str)[i], ";") == 0 && i != 0) {
            temp = copy_strarr(*input_str, i);
            (*input_str) += sizeof(char) * (i + 1);
            (*shift) += sizeof(char) * (i + 1);
            return temp;
        }   
    }
    return *input_str;

}
