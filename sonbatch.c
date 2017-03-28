#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
 
#define MAXCHAR 1000


int main() {
    FILE *fp;
    char str[MAXCHAR];
    char *filename = "commands";
    char *noktalivirgul;

    pid_t wpid, pid, parent_pid;
    int status = 0;
    

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        printf(" --- okudugum %s\n", str);
        
        noktalivirgul = strstr(str, ";");

        if(noktalivirgul != NULL)
        {
            printf("ENCOUNTER ; NEED CHILD\n");
            char *p = strtok(str, ";");

            while(p != NULL)
            {
                
                if(strcmp(p,"quit") == 0)
                {
                    printf("Quit code" );
                }

                else 
                {
                    pid = fork();
                    if(pid < 0)
                    {
                        fprintf(stderr, "Fork failed");
                    }

                    else if (pid == 0)
                    {
                         pid = getpid();
                         printf("I AM THE CHILD AND MY PID:    %d\n",pid );
                         printf("I AM DOING >>>  %s\n",p);

                         system(p);
                         p = strtok(NULL, ";");
                         status = 0;
                    }

                    else
                    {
                     printf("parent_pid  = %d\n", pid);
                     waitpid(pid, &status,0);
                     exit(0);
                    }
                }
                
            }
        }

        else
        {
            printf("I DO NOT NEED CHILD I AM PARENT AND DOING >>> %s\n",str);
            system(str);      
        }

    }

    fclose(fp);
    return 0;
}
