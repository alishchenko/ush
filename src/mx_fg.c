#include "../inc/ush.h"

static void print_msg(char *name, int proc_num) {
    mx_printchar('[');
    mx_printint(proc_num);
    mx_printchar(']');
    mx_printstr("  - continued ");
    mx_printstr(name);
    mx_printchar('\n');
}

static int get_pindex(char *pname) {
    for(int i = size_p - 1; i >= 0; i--) {
        if(mx_strcmp(pname, proc_names[i]) == 0)
            return i;
    }
    return -1;
}

void mx_fg(char **parsed) {
    int proc_num = size_p - 1;
    if(parsed[1] != NULL) { //processing arguments
        proc_num = mx_atoi(parsed[1]);

        if(proc_num == 0) proc_num = get_pindex(parsed[1]);
        else proc_num--;

        if(proc_num >= size_p || (proc_num + 1) < 1) {              
            mx_printerr("fg: job not found: ");
            mx_printerr(parsed[1]);
            mx_printerr("\n");
            return;
        }
    }
    
    if(paused_processes == NULL) {
        mx_printstr("fg: no current job\n");
        return;
    }
    
    child_pid = paused_processes[proc_num]; //changing current procces 
    if(procces_name) mx_strdel(&procces_name);
    procces_name = mx_strdup(proc_names[proc_num]);

    if(parsed[1]) { 
        arr_pop_index(&paused_processes, proc_num, size_p);
        strarr_pop_index(&proc_names, proc_num, size_p);
    }
    else {
        arr_pop_back(&paused_processes, size_p); 
        strarr_pop_back(&proc_names, size_p);
    }
    size_p--;
    
    print_msg(procces_name, proc_num + 1);
    
    //printf("pid cont %d\n", child_pid);
    kill(child_pid, SIGCONT);
    (void)signal(SIGCONT, SIG_DFL);
    waitpid(child_pid, &status, WUNTRACED);
    
    if(WIFSTOPPED(status)) {
        mx_printstr("\nush: suspended ");
        mx_printstr(procces_name);
        mx_printchar('\n');
    }
    
}
