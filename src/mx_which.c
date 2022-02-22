#include"../inc/ush.h"

char *reserved_words[22] = {"if", "then", "elif", "else", "fi", "time",
 "for",	"in", "until" , "while", "do", "done", "case",
 "esac", "coproc", "select", "function",
 "{", "}", "[[", "]]", "!"};

char *build_in_comands[60] = {":", ".", "[", "alias", "bg", "bind", "break", "builtin", "case",
 "cd", "command", "compgen", "complete", "continue", "declare", "dirs", "disown", "echo",
  "enable", "eval", "exec", "exit", "export", "fc", "fg", "getopts", "hash", "help", "history",
   "if", "jobs", "kill", "let", "local", "logout", "popd", "printf", "pushd", "pwd", "read",
    "readonly", "return", "set", "shift", "shopt", "source", "suspend", "test", "times", "trap",
	 "type", "typeset", "ulimit", "umask", "unalias", "unset", "until", "wait", "while", "\0"}; 

static int count_args(char **args) {
    int i;
    for(i = 0; args[i] != NULL; i++);
    return i;
}

bool check_reserved_comands(char** parsed) {
	for(int i = 1; parsed[i] != NULL; i++) {
		for(int j = 0; build_in_comands[j]; j++) {
			if(mx_strcmp(parsed[i], build_in_comands[j]) == 0) {
				mx_printstr(build_in_comands[j]);
				mx_printstr(": ush built-in command\n");
			}
		}
	}
	return true;
}


bool check_reserved_words(char** parsed) {
	for(int i = 1; parsed[i] != NULL; i++) {
		for(int j = 0; j < 22; j++) {
			if(mx_strcmp(parsed[i], reserved_words[j]) == 0) {
				mx_printstr(reserved_words[j]);
				mx_printstr(": ush reserved word\n");
				return false;
			}
		}
	}
	return true;
}

int parse_flag(char** args, bool *flag_a, bool *flag_s) {
    int z = 0;
    for(int i = 0; args[i] != NULL; i++) {
        if(args[i][0] == '-') {
            z++;
            for(int j = 0; j < mx_strlen(args[i]); j++) {
                if(args[i][j] == 'a') *flag_a = true;
				else if(args[i][j] == 's') *flag_s = true;
				else if(args[i][j] == '-') continue;
				else {
					mx_printstr("which: bad option: -");
					mx_printchar(args[i][j]);
					mx_printchar('\n');
					return -1;
				}

            }
        }
    }
    return z;
}

int search_proga(char *str, bool flag_s, char *dir) {
    DIR *dir1 = NULL;
    struct dirent *dir2;
    int flag = 1;
    
    dir1 = opendir(dir);
    if (!dir1)
        return 1;
    dir2 = readdir(dir1);
    while (dir2 != NULL) {
        if (mx_strcmp(dir2->d_name, str) == 0) {
            if (flag_s) {
                mx_printstr(dir);
                mx_printchar('/');
                mx_printstr(dir2->d_name);
                mx_printchar('\n');
            }
            flag = 0;
            break;
        }
        dir2 = readdir(dir1);
    }
    closedir(dir1);
    return flag;
}

int go_into_dir(char *str, bool *flag_a, bool *flag_s, int flag) {
    char *temp = NULL;
    int y = 0;
    int r = 0;
    char *dir = NULL;
    int b = 0;
   
    int n = 1;
    temp = getenv("PATH");
    for (; r != -1; y = y + r + 1) {
        r = mx_get_char_index(&temp[y], ':');
        dir = mx_strnew(mx_strlen(temp));
        for (b = y; r >= 0 ? b < r + y : temp[b] != '\0'; b++)
            dir[b - y] = temp[b];
        if ((flag = search_proga(str, flag_s, dir)) == 1)
            continue;
        dir = NULL;
        n = flag == 0 ? 0 : n;
        if (flag == 0 && !flag_a)
            break;
    }
    return n;
}

void mx_which(char** parsed) {
	int size = count_args(parsed);
	bool flag_a = false;
	bool flag_s = false;

	int res = 0;
	if(size == 1) return;
	int parse_flag_res = parse_flag(parsed, &flag_a, &flag_s);

	if(parse_flag_res < 0) return;
	if(!check_reserved_words(parsed)) return;
    if(!check_reserved_comands(parsed)) return;

	int flag = 0;

	for (int i = 1 + parse_flag_res; i < size; i++) {
        flag  = go_into_dir(parsed[i], &flag_a, &flag_s, parse_flag_res);
        res = parse_flag_res ? 1 : res;
        if (flag  == 1 && !flag_s) {
            write(2, parsed[i], mx_strlen(parsed[i]));
            write(2, " not found\n", 11);
        }
    }
}



