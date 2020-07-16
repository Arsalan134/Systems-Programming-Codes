


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <dirent.h>
#include <stdbool.h>
//#include <wait.h>

struct cmd {
    char* cmdStr;
    int cmdSize;
} command;

struct cmd getCommand() {
    int space = 1;
    char buf[1];
    
    struct cmd command;
    command.cmdStr = malloc(space);
    command.cmdSize = 0;
    
    while(read(STDIN_FILENO, buf, 1)) {
        if(buf[0] != '\n') {
            command.cmdStr[command.cmdSize++] = buf[0];
            command.cmdStr = realloc(command.cmdStr, ++space);
        }
        else break;
    }
    command.cmdStr[command.cmdSize] = '\0';
    return command;
}

int main(int argc, char const *argv[]) {
    char *quote = malloc(300 * sizeof(char));
    quote = "\n###############################################\n### Nobody can give you freedom ###############\n### Nobody can give you equality or justice ###\n### If you are a man, you take it #############\n####### -Malcolm X- ###########################\n\n";
    
    pid_t pid = fork(); // get id for a child
    
    if (pid == 0) { /* Child process */
    
    write(STDOUT_FILENO, quote, 242);
        
        
    
    bool ifExit = false;
    int exitStatus = -1;
    
    write(STDOUT_FILENO, "$ ", 2);
    
    struct cmd command;
    command = getCommand();
    
    bool emptyCmd = false;
    if (!strcmp(command.cmdStr, "")) emptyCmd = true;
    char * binFile = malloc(1000);
    char ** cmdParts = malloc(1000);
    int cmdSpace = 0;
    char * token;
    
    token = strtok(command.cmdStr, " ");
    while (token != NULL) {
        cmdParts[cmdSpace] = token;
        cmdSpace++;
        token = strtok(NULL, " ");
    }
        
    cmdParts[cmdSpace] = token;
    cmdParts = realloc(cmdParts, sizeof(char*) * cmdSpace);
    
    bool cmdNotFound = false;
    if (!emptyCmd) {
        execvp(binFile, cmdParts);
        wait(&waitst);
        exitStatus = WEXITSTATUS(waitst);
    }
    return exitStatus;
}

