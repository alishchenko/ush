#include "../inc/ush.h"

pid_t *paused_processes = NULL;
char **proc_names = NULL;
int size_p = 0;

void signal_catcher(int sig) { 
  switch(sig) {
    case SIGINT:
        if(child_pid != 0) {
            //printf("catch SIGINT1 pid %d i`m in %d\n", child_pid, getpid());
            kill(child_pid, sig);
            if(size_p > 0 && child_pid == paused_processes[size_p - 1]) {
                arr_pop_back(&paused_processes, size_p); 
                strarr_pop_back(&proc_names, size_p);
                size_p--;
            }
            child_pid = 0;
            (void)signal(SIGINT, SIG_DFL);
            mx_printstr("\n");
        }
        else {
            mx_printstr("\nu$h> ");
        }
        break;
    case SIGTSTP:
        //printf("GOT STOP SIGNAL\n");
        if(!is_in_arr(paused_processes, child_pid, size_p)) {
            arr_push_back(&paused_processes, child_pid, size_p);
            strarr_push_back(&proc_names, procces_name, size_p); 
            size_p++;
        }
        child_pid = 0;
        

        kill(paused_processes[size_p - 1], sig);
        (void)signal(SIGTSTP, SIG_DFL); 
        break; 
    default:
        (void)signal(sig, SIG_IGN); 
  }
  
}
