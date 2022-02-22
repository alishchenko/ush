#include "../inc/ush.h"
// Function to execute builtin commands
int exec_own_cmds(char** parsed) {

    int amount = 10, switch_args = 0;
    char* cmd_list[amount];
    cmd_list[0] = "exit";
    cmd_list[1] = "cd";
    cmd_list[2] = "pwd";
    cmd_list[3] = "help";
    cmd_list[4] = "export";
    cmd_list[5] = "unset";
    cmd_list[6] = "echo";
    cmd_list[7] = "fg";
    cmd_list[8] = "which";
    cmd_list[9] = "env";

  
    for (int i = 0; i < amount; i++) {
        if (mx_strcmp(parsed[0], cmd_list[i]) == 0) {
            switch_args = i + 1;
            break;
        }
    }
    switch (switch_args) {
    case 1:
        mx_exit(parsed);
    case 2:
        mx_cd(parsed);
        return 1;
    case 3:
        mx_pwd(parsed);
        return 1;
    case 4:
        mx_printstr("No one will help you, live in a cursed world you`ve create.\n");
        return 1;
    case 5:
        mx_export(parsed);
        return 1;
    case 6:        
        mx_unset(parsed);
        return 1;
    case 7:
        mx_echo(parsed);
        return 1;
    case 8:
        mx_fg(parsed);
        return 1;
    case 9:
        mx_which(parsed);
        return 1;
    default:
        break;
    }
    return 0;
}
