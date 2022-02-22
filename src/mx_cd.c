#include "../inc/ush.h"

#define ENV_UPDATE setenv("PWD", cur_path, 1); setenv("OLDPWD", prev_path, 1);

char *prev_path = NULL;
char *cur_path = NULL;
bool was_in_link;

static void get_new_pathes(char **prev_path, char **cur_path) {
        mx_strdel(prev_path);
        *prev_path = mx_strdup(*cur_path);
        mx_strdel(cur_path);
        *cur_path = malloc(sizeof(char) * 1024);
        getcwd(*cur_path, 1024);
        setenv("PWD", *cur_path, 1);
        setenv("OLDPWD", *prev_path, 1);
}

static int count_args(char **args) {
    int i;
    for(i = 0; args[i] != NULL; i++);
    return i;
}

static void check_flags(char **args, bool *fl_P, bool *fl_s) {
    for(int i = 0; args[i] != NULL; i++) {
        if(mx_strcmp(args[i], "-") != 0 && args[i][0] == '-') {
            for(int j = 0; j < mx_strlen(args[i]); j++) {
                if(args[i][j] == 'P') *fl_P = true;
                else if(args[i][j] == 's') *fl_s = true;
            }
        }
    }
}

void mx_cd(char **args) {
    struct stat buf;
    bool fl_P = false, fl_s = false;
    int argc = count_args(args);
    check_flags(args, &fl_P, &fl_s);
    char *path = args[argc - 1]; 
    char* link_path;
    if(!prev_path) { //init pathes
        prev_path = malloc(sizeof(char) * 1024);
        getcwd(prev_path, 1024);
        cur_path = mx_strdup(prev_path);
        ENV_UPDATE
    }
    
    
    if(mx_strcmp(path, "cd") == 0) { //cd without path
        chdir(getenv("HOME"));
        get_new_pathes(&prev_path, &cur_path);
        return;
    }
    if(path[0] != '/') {
        link_path = path ? update_path(path) : NULL;
    }
    else link_path = path;

    if(mx_strcmp(path, "-") == 0) { //cd - 
        char *temp = mx_replace_substr(prev_path, getenv("HOME"), "~");
        mx_printstr(temp);
        mx_printchar('\n');
        mx_strdel(&temp);
        chdir(prev_path);
        swap_strings(&prev_path, &cur_path);
        ENV_UPDATE
        return;
    }
    
    if(was_in_link && mx_strcmp(path, "..") == 0) {
        char *lpath = mx_strdup(getenv("LINKPATH"));
        mx_str_reverse(lpath);
        char *lfpath = mx_strchr(lpath, '/');
        mx_str_reverse(lfpath);
        chdir(lfpath);
        mx_strdel(&cur_path);
        cur_path = malloc(sizeof(char) * 1024);
        getcwd(cur_path, 1024);
        mx_strdel(&prev_path);
        prev_path = mx_strdup(getenv("LINKPATH"));
        ENV_UPDATE
        was_in_link = false;
        return;
    }

    lstat(path, &buf);
    errno = 0;
    
    if(fl_s && S_ISLNK(buf.st_mode)) { //-s
        mx_printerr("cd: not a directory: ");
        mx_printerr(path);
        mx_printerr("\n");
        return;
    }

    if(S_ISLNK(buf.st_mode) && !fl_P) { //LINKS
        was_in_link = true; 
        setenv("LINKPATH", link_path, 1);
        mx_strdel(&cur_path);
        cur_path = mx_strdup(link_path);
        mx_strdel(&prev_path);
        prev_path = mx_strdup(getenv("PWD"));
        ENV_UPDATE
        chdir(path);
        return;
    }
    

    if(path[0] == '$') {
        path = mx_replace_substr(path, "{", "");
        path = mx_replace_substr(path, "}", "");
        path++;
        if(getenv(path) == NULL)
            chdir(getenv("HOME"));
        else 
            chdir(getenv(path));
        path--;
    }
    else
        chdir(path); //default
   
    
    if(errno == ENOENT) {
        mx_printerr("cd: no such file or directory: ");
        mx_printerr(path);
        mx_printerr("\n");
        return;
    }

    get_new_pathes(&prev_path, &cur_path);
    
}
