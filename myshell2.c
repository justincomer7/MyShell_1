#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "mycommands2.h"

int main(int argc, char **argv, char **envp) {
  char * line = (char * ) malloc(BUFFSIZE * sizeof(char));
  int status = 0;
  char * exit = (char * ) malloc(4 * sizeof(char));

  char * en = (char * ) malloc(2 * sizeof(char));

  char * * commands = malloc(BUFFSIZE * 2 * sizeof(char * ));
  strcpy(exit, "exit");
  	commands[0] = exit;
  strcpy(en, "env");
  	commands[1] = en;
  
  int size = sizeof(commands) / sizeof(commands[0]);
  welcome();

  int z; //variable z will be used for strcomp in our cat function

  do {
    printf(">");
    line = read_line();

    char * * parsed = malloc(BUFFSIZE * sizeof(char * ));

    parsed = parser(line);

    int i, found = 0;
    for (int l = 0; l < 2; l++) {
      if (strcmp(parsed[0], commands[l]) == 0) {
        found = 1;
        i = l;
        break;
      }
    }

    if (found == 0) {
      printf("%s: command not found\n", parsed[0]);
    } else
      switch (i) {

        /*exit*/
      case (0):
        return 0;
        break;
        /*env*/
      case (1):
        {
          if (parsed[1] == NULL) {
            env_print(envp);
			}
			
			else
				printf("env: %s: No such file or directory\n", parsed[1]);
        }
        break;
	  }
	 
	}while( status != 1);
}