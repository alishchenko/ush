#include "../inc/ush.h"

static void shlvl_() {
    int shlvl = mx_atoi(getenv("SHLVL"));
    shlvl++;
    setenv("SHLVL", mx_itoa(shlvl), 1);
}

int main() {
    char inputString[MAXCOM], **parsedArgs;
    int amount, i = 0, shift = 0;
    char **cmds;
    shlvl_();
    while (true) {
        (void)signal(SIGINT, signal_catcher);
        (void)signal(SIGTSTP, signal_catcher);

        parsedArgs = malloc(sizeof(char*) * MAXLIST);
        // take input
        if (get_input(inputString))
            continue;
        // process
        
        if(!validate_input(inputString, parsedArgs)) { 
            continue; 
        }
        amount = get_amount_cmds(parsedArgs);
        //mx_print_strarr(parsedArgs, " ");
        // execute
        do {
            cmds = fix_command_list(&parsedArgs, &shift); // separator processing
            if(!exec_own_cmds(cmds))
                exec_sys_cmds(cmds);
            i++;
        } while (i < amount);
        parsedArgs -= shift;
        i = 0; shift = 0;
        if(parsedArgs) mx_del_strarr(&parsedArgs);
    }
    return 0;
}

