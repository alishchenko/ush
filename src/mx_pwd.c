#include "../inc/ush.h"

static void parce_flag_pwd(char** args, bool* fl_P ) {
    
    for(int i = 0; args[i] != NULL; i++) {
        
        if(args[i][0] == '-') {
            
            for(int j = 0; j < mx_strlen(args[i]); j++) {
                
                if(args[i][j] == 'P') *fl_P = true;
            }
            
        }
        
    }
}

void mx_pwd(char** argc) {
    struct stat buf;
    bool fl_P = false;
    parce_flag_pwd(argc, &fl_P);
    lstat(getenv("PWD"), &buf);
    if(fl_P && S_ISLNK(buf.st_mode)) {
        char *temp_buf = mx_strnew(1024);
        readlink(getenv("PWD"), temp_buf, 1024);
        mx_printstr(temp_buf);
        mx_strdel(&temp_buf);
    }
    else mx_printstr(getenv("PWD"));
    mx_printchar('\n');
}
    
    
