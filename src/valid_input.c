#include "../inc/ush.h"

static char* parse_quotes(char **str, char quote) {
    (*str)++;
    char *new_str = NULL;
    int size = 0;
    while(*(*str) != quote) {
        if(**str == '\0') {
            mx_printerr("Odd number of quotes.\n");
            if(new_str) mx_strdel(&new_str);
            return NULL;
        }
        str_push_back(&new_str, **str, size);
        size++; (*str)++;
    }
    return new_str;
}

static char *parse_tilda(char *str, int *size, int *error_flag) {
    if(str[1] == '/' || str[1] == '\0' || str[1] == ' ' || str[1] == ';') {
        (*size) += mx_strlen(getenv("HOME"));
        return mx_strdup(getenv("HOME"));
    }
    else {
        char *temp = NULL; int size_temp = 0;
        bool user_found = false;
        for(int i = 1; str[i] != ' ' && str[i] != '\0' && str[i] != ';' && str[i] != '/' ; i++) {
            str_push_back(&temp, str[i], size_temp++);
        }
        DIR *dir;
        struct dirent *entry;
        dir = opendir("/Users");
        if (!dir) {
            perror("diropen");
            return NULL;
        }
        while ((entry = readdir(dir)) != NULL) {
            if(mx_strcmp(entry->d_name, temp) == 0) {
                user_found = true;
                break;
            }
        }
        closedir(dir);
        if(!user_found) {
            mx_printerr("ush: no such user or named directory: ");
            mx_printerr(temp);
            mx_printerr("\n");
            *error_flag = -1;
            return NULL;
        }
        (*size) += 7;
        return mx_strdup("/Users/");
    }
}

int validate_input(char* str, char** parsed) {
    char *temp = NULL;
    int size = 0, k = 0, error_flag = 0;
    for(; *str != '\0'; str++) {
        if(*str == '\"' || *str == '\'') { //kovichki
            temp = parse_quotes(&str, *str);

            if(!temp) return 0;

            parsed[k] = mx_strdup(temp); k++;
            if(temp) mx_strdel(&temp); size = 0;
            continue;

        }
        else if(*str == ';') { //fix sepatatora
            if(temp) {
                parsed[k] = mx_strdup(temp); 
                parsed[k + 1] = mx_strdup(";");
                k += 2;
                if(temp) mx_strdel(&temp); size = 0;
            }
            else if(!temp && k > 0) {
                parsed[k] = mx_strdup(";"); k++;
            }
            continue;
        }

        else if(*str == '~') {  // ~ fix
            char *temp_2 = parse_tilda(str, &size, &error_flag);
            if(error_flag == -1) {
                if(temp) mx_strdel(&temp);
                return 0;
            }
            temp = realloc(temp, size);
            temp = strcat(temp, temp_2);
            continue;
        }

        else if(*str == '\\' && str[1] == ' ') { //spaces in names
            str_push_back(&temp, ' ', size++);
            str++;
            continue;
        }
        else if(*str == '\\' && str[1] == '`') { // ` in names
            str_push_back(&temp, '`', size++);
            str++;
            continue;
        }
        else if(*str != ' ') {
            str_push_back(&temp, *str, size++);
        }
        else if(*str == ' ' && temp) {
            parsed[k] = mx_strdup(temp); k++;
            if(temp) mx_strdel(&temp); size = 0;
        }
    }
    
    if(temp) {
        parsed[k] = mx_strdup(temp);
        mx_strdel(&temp);
        k++;
    }
    parsed[k] = NULL;
    
    if(mx_strcmp(parsed[k - 1], ";") == 0) parsed[k - 1] = NULL; 
    //mx_print_strarr(parsed, " ");
    return 1;
}
