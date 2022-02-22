#include"../inc/ush.h"

void check_correct_arg_curved_br(char* param, int *error) {
    int open_curved_br = 0;
    int close_curved_br = 0;

    int open_round_br = 0;
    int close_round_br = 0;

    int apostrov = 0;

    char* str = mx_strdup(param);

    while (*str != '\0')
    {
        if(*str == '{') open_curved_br++;
        if(*str == '}') close_curved_br++;

        if(*str == '(') open_round_br++;
        if(*str == ')') close_round_br++;

        if(*str == '`') apostrov++;
        
        str++;
    }
    if(open_curved_br < close_curved_br) {
        *error = -1;
        mx_printerr("u$h: parse error near `}");
        mx_printerr("\'\n");
        return;
    }
    if(open_curved_br > close_curved_br) {
        *error = -1;
        mx_printerr("u$h: bad substitution\n");
        return;
    }

    if(open_round_br < close_round_br) {
        *error = -1;
        mx_printerr("u$h: parse error near `)");
        mx_printerr("\'\n");
        return;
    }
    if(open_round_br > close_round_br) {
        *error = -1;
        mx_printerr("u$h: bad substitution\n");
        return;
    }
}

char * mx_parce_dollar_curved_br(char* param, char** result, int *error) {
    if (*result) mx_strdel(result);
    char* str = mx_strchr(param, '$');
    check_correct_arg_curved_br(param, error);
    if(*error < 0) return NULL;
    if(str == NULL || ++str == NULL) return NULL;
    bool is_open_br = false;
    if(*str == '{' && ++str != NULL) is_open_br = true;   

    if(is_open_br) {

        while (*str != '\0')
        {
            if(*str == '{'){
                *error = -1;
                mx_printerr("u$h: bad substitution\n");
                return NULL;
            }
            if(*str == '}') {
                return ++str;
            }
            if(*str == '$') {
                
                return str;
            }
            *result = mx_strjoin(*result, mx_strndup(str++, 1));
            //str++;
        }
        return NULL;
    } else {

        while (*str != '\0')
        {
            if(*str == '}') {
                *error = -1;
                mx_printerr("u$h: parse error near asda`");
                mx_printchar(*str);
                mx_printerr("\'\n");
                return NULL; 
            }
            if(*str == '$' || *str == '(') {
                return str;
            }
            *result = mx_strjoin(*result, mx_strndup(str, 1));
            str++;
        }
        return NULL;
    }
}

char * mx_parce_dollar_round_br(char* param, char** result, int *error) {
    if (*result) mx_strdel(result);
    char* str = mx_strchr(param, '$');
    if(str == NULL || ++str == NULL) return NULL;
    bool is_open_br = false;
    if(*str == '(' && ++str != NULL) is_open_br = true;   

    if(is_open_br) {

        while (*str != '\0')
        {
            if(*str == '(') {
                *error = -1;
                mx_printerr("u$h: bad substitution");
            }
            if(*str == ')') {
                return ++str;
            }
            if(*str == '$') {
                return str;
            }
            *result = mx_strjoin(*result, mx_strndup(str++, 1));
            //str++;
        }
        return NULL;
    }
    return NULL;
}
// Делайте парсер 😅
// Что бы все эти херобины \ / ‘ ~ $ корректно работали 

// Я ж приду буду сигналы дальше пытаться делать

