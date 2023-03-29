#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LINE 80

void excuteFunction(char **args, char *arg, int commandNum){
    while (arg != NULL) {    
        args[commandNum++] = arg;
        arg = strtok(NULL, " ");               
    } 
    
    args[commandNum++] = NULL;

    execvp(args[0], args);
}

int main(void)
{
    char *hitoryCommand[20];
    char *args[MAX_LINE/2 +1];
    int should_run  = 1;
    int historyNum = 0;
    pid_t pid;
    int useHistoryMalloc = 0;

    while (should_run){
        printf("osh>");
        fflush(stdout);

        char inputline[100];

        fgets(inputline, 100, stdin); 
        inputline[strlen(inputline) - 1] = 0;  
        int should_wait = 1; 
        
        pid = fork();
        
        if (pid == 0){ 
            char * inputlineCopy = malloc(strlen(inputline) * sizeof(char));
            strcpy(inputlineCopy , inputline);

            int commandNum = 0;
            char *arg = strtok(inputline, " ");

            if (strcmp(arg, "history") == 0){
                
                char *secondC = strtok(NULL, " ");

                if (secondC == NULL){
                    for (int i = 0; i < historyNum; i++) printf("%d : %s\n", i + 1, hitoryCommand[i]);
                    break;            
                }

                int num = atoi(secondC);

                if (num > historyNum) {
                    printf("not record yet\n");
                    break;
                }      

                num -= 1;

                if (hitoryCommand[num][strlen(hitoryCommand[num]) - 1] == '&'){
                    should_wait = 1;
                    hitoryCommand[num][strlen(hitoryCommand[num]) - 1] = 0;
                }

                int commandNum = 0;
                char *arg = strtok(hitoryCommand[num], " ");

                excuteFunction(args, arg, commandNum);
            }else{
                pid_t excutePid = fork();

                if (excutePid == 0){
                    if (inputlineCopy[strlen(inputlineCopy) - 1] == '&'){
                        should_wait = 1;
                        inputlineCopy[strlen(inputlineCopy) - 1] = 0;
                    }

                    char *arg = strtok(inputlineCopy, " ");

                    excuteFunction(args, arg, commandNum);       
                }else{
                    wait(NULL);
                    hitoryCommand[historyNum] = malloc(strlen(inputlineCopy) * sizeof(char));
                    useHistoryMalloc = 1;
                    strcpy(hitoryCommand[historyNum], inputlineCopy);
                    historyNum += 1;
                    free(inputlineCopy);
                }
            }

            should_run = -1;
        } else if (pid > 0) {
             if (should_wait == 1) {
                wait(NULL); // wait for child process to complete
            }     
        } else {
            printf("error");
        }
    }
    return 0;
}