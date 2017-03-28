#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

char *gets(char *str);

int main(int argc, char* argv[]){

  char input[50];
  char command[50];
  char *inputptr;
  
  pid_t wpid, pid, parent_pid;
  int status = 0;

  char *noktalivirgul;

  inputptr = input;

  printf("todo:>");

  gets(inputptr);

  while(strcmp(inputptr, "quit")!= 0) {

     sprintf(command, "\"%s\"", input);

     noktalivirgul = strstr(inputptr, ";");

     if(noktalivirgul != NULL)
     {
        char *p = strtok(inputptr, ";");

        while(p != NULL)
        {
          printf("WE NEED CHILDS NOW \n");
          pid = fork();

          if(pid < 0)
          {
            fprintf(stderr, "Fork failed");
          }

          else if(pid == 0)
          { 
            pid = getpid();
            printf("I AM THE CHILD AND MY PID:    %d\n",pid );
            printf("WE ARE DOING >>>  %s\n",p);

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
          printf("todo:>");
          gets(inputptr);
     }
     else 
     {
      printf("I DO NOT NEED CHILD I AM PARENT AND DOING >>> %s\n",input);
      system(input);      
      printf("todo:>");
      gets(inputptr);
     }    
  }
  return 0;
}  