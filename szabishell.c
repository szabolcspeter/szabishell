#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 

int main(int argc, char* argv[])
{
  char buf[1024];
  ssize_t len;
  char* token, *commandline[100];
  int /*argcount,*/ i, pid;

  while (1)
  {
    printf(">> ");
    if (!fgets(buf, sizeof(buf), stdin)) break;
    len = strlen(buf);
    if (buf[len-1] == '\n') buf[len-1] = '\0';
    token = strtok(buf, " ");
    i = 0;     
    while (token)
    {
      commandline[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    commandline[i] = NULL;
    /*argcount = i;
    for (i=0; i<argcount; i++)  printf("%s\n", commandline[i]);*/
    
    pid = fork();
    if (pid == 0)
    {
      execvp(commandline[0], commandline);
    }
    else
    {
      wait(NULL);
    }
    
  }
  printf("\n");
  return EXIT_SUCCESS;
}
