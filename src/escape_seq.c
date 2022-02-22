#include "../inc/ush.h"

char *escape_seq(char *line) {
    char *res = mx_strnew(strlen(line)), *temp = res;
    while (*line) {
        if (*line == '\\') {
            line++;
            switch (*line) {
            case '\\':
                *temp = '\\';
                temp++;
                break;
            case 'a':
                *temp = '\a';
                temp++;
                break;
            case 'b':
                *temp = '\a';
                temp++;
                break;
             case 'f':
                *temp = '\f';
                temp++;
                break;
             case 'n':
                *temp = '\n';
                temp++;
                break;
             case 'r':
                *temp = '\r';
                temp++;
                break;
             case 't':
                *temp = '\t';
                temp++;
                break;
             case 'v':
                *temp = '\v';
                temp++;
                break;
            default:
                *temp = '\\'; temp++;
                *temp = *line; temp++;
                break;
            }
        }
        else {
            *temp = *line;
            temp++;
        }
        line++; 
    }
    return res;
}
