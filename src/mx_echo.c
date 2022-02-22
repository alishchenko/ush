#include "../inc/ush.h"

int parse_flag_echo(char** args, bool *flag_n, bool *flag_e, bool *flag_E) {
    args++;
    int res = 1;
    for(int i = 0; args[i] != NULL && args[i][0] == '-'; i++) {
        for(int j = 1; j < mx_strlen(args[i]); j++) {
            if(args[i][j] == 'e' && ++res) *flag_e = true;
            else if(args[i][j] == 'n' && ++res) *flag_n = true;
            else if(args[i][j] == 'E' && ++res) *flag_E = true;
            else return res;
        }
    }
    return res;
}

void mx_echo(char **args) {
    int error = 0;

    bool flag_n = false, flag_e = false, flag_E = false, bool_enter = false;
    int res = parse_flag_echo(args, &flag_n, &flag_e, &flag_E);
    while (--res > 0) ++args;
    if (args) args++;
    while (args && *args) {
        char* name = NULL;
        char* srt_args;

        if (flag_e || !flag_E) {
            srt_args = escape_seq(*args);
        }
        else srt_args = strdup(*args);
        while (srt_args != NULL && *srt_args != '\0') {
            char *temp = mx_parce_dollar_curved_br(srt_args, &name, &error);
            
            if(error < 0) return;

            while (*srt_args != '\0' && *srt_args != '$' && *srt_args != '{' && *srt_args != '(' && *srt_args != '`') {
                mx_printchar(*srt_args);
                bool_enter = false;
                srt_args++;
            }
            if (*srt_args != '\0') {
                if (name) {
                    extern char **environ;
                    for (int i = 0; environ[i] != NULL; i++) {
                        if(mx_strncmp(name, environ[i], mx_get_char_index(environ[i], '=')) == 0) {
                            mx_printstr(&(environ[i][mx_get_char_index(environ[i], '=') + 1]));
                            break;
                        }
                    }
                    bool_enter = false;
                }
                else {
                    temp = mx_parce_dollar_round_br(srt_args, &name, &error);

                    if(error < 0) return;
                    if (name) {
                        //printf("stroka: %s\n", name);
                        char **kostyl = malloc(sizeof(char**) * 2);
                        kostyl[0] = name; 
                        kostyl[1] = NULL;
                        if(!exec_own_cmds(kostyl))
                            exec_sys_cmds(kostyl);
                        bool_enter = true;
                    }
                    else if ((temp = mx_strchr(srt_args, '`')) != NULL) {
                        while (++temp) {
                            if (*temp == '`') {
                                temp++;
                                break;
                            }
                            name = mx_strjoin(name, mx_strndup(temp, 1));                            
                        }
                        char **kostyl = malloc(sizeof(char**) * 2);
                        kostyl[0] = name; 
                        kostyl[1] = NULL;
                        if(!exec_own_cmds(kostyl))
                            exec_sys_cmds(kostyl);
                        bool_enter = true;
                    }
                    else {
                        if (mx_strlen(srt_args) > 1)
                            mx_printstr(srt_args);
                        else
                            mx_printchar(*srt_args);
                        args++;
                        if (*args) mx_printstr(" ");
                        args--;
                        bool_enter = false;
                    }
                }            
                //if (srt_args) mx_strdel(&srt_args);
                srt_args = NULL;
                if (temp) {
                    srt_args = mx_strdup(temp);
                    //mx_strdel(&temp);
                }
            }
            else srt_args = NULL;
        }
        args++;
        if (*args) mx_printchar(' ');
    }
    if (!bool_enter) mx_printstr("\n");
}
/*
echo 2 3 4$USER$NAME
echo ${NAME}*/
