#include "../inc/ush.h"

pid_t child_pid;
int status;
char *procces_name = NULL;

static bool check_comands(char* cmd) {
    char *tmp = mx_strdup(cmd);
    char *nasty_commands[9] = {"nano", "cat", "vim", "emacs", "top", "./ush", "sh", "bash", NULL};
		for(int j = 0; nasty_commands[j]; j++) {
			if(mx_strcmp(tmp, nasty_commands[j]) == 0) {
                mx_strdel(&tmp);
				return false;
			}
		}
    mx_strdel(&tmp);
	return true;
}

// Function where the system command is executed
void exec_sys_cmds(char** parsed) {
    pid_t pid = fork();
    child_pid = pid; 
    //if(procces_name) mx_strdel(&procces_name);
    procces_name = mx_strdup(parsed[0]);
    if (pid == -1) {
        mx_printerr("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        if(check_comands(parsed[0])){
            setpgid(getpid(), getpid());
        }
        //printf("child pid %d\n", getpid());
        if (execvp(parsed[0], parsed) < 0) {
            mx_printerr("ush: command not found: ");
            mx_printerr(parsed[0]);
            mx_printerr("\n");
        }
        
        // signal(SIGHUP, SIG_IGN);
        // signal(SIGTERM, SIG_IGN);
        exit(0);
    } else {
        // waiting for child to terminate'
        waitpid(child_pid, &status, WUNTRACED);
        if(WIFEXITED(status)) {
           // mx_printstr("CHILD DEAD\n");
            if(procces_name) mx_strdel(&procces_name);
            child_pid = 0;
        }
        if(WIFSTOPPED(status)) {
            mx_printstr("\nush: suspended ");
            mx_printstr(procces_name);
            mx_printchar('\n');
            if(procces_name) mx_strdel(&procces_name);
        }
            //wait(NULL); 
        return;
    }
}
