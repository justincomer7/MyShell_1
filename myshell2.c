#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "mycommands2.h"

 char * * commands; // creates global variables 
 char **env;

int get_size(char ** array){ // get size of array of strings 
	int size = 0;
	while(array[size] != NULL)
			size++;
		
	return size;
}

void run_commands (char *line){ 
    int i, found = 0;
	char * * parsed = malloc(BUFFSIZE * sizeof(char * ));

    parsed = parser(line);
    for (int l = 0; l < get_size(commands); l++) {
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
        exit(0);
        break;
        /*env*/
      case (1):
        {
          if (parsed[1] == NULL) {
            env_print(env);
			}
			
			else
				printf("env: %s: No such file or directory\n", parsed[1]);
        }
        break;
	  case (2):
		{
			printf("timeout repeated\n");
		}
	  }
}



int main(int argc, char **argv, char **envp) {
	env = envp;
	char * line = (char * ) malloc(BUFFSIZE * sizeof(char));
  int status = 0;
  char * exit = (char * ) malloc(4 * sizeof(char));
  char * en = (char * ) malloc(2 * sizeof(char));
  char * ti = (char * ) malloc(7 * sizeof(char));
  
  commands = malloc(BUFFSIZE * 2 * sizeof(char * ));

 
  strcpy(exit, "exit");
  	commands[0] = exit;
  strcpy(en, "env");
  	commands[1] = en;
  strcpy(ti, "timeout");
	commands[2] = ti;
  
  
  welcome();

  int z; //variable z will be used for strcomp in our cat function

  do {
    printf(">");
    line = read_line();

    char * * parsed = malloc(BUFFSIZE * sizeof(char * ));

    parsed = parser(line);
	
	//checks to see if timeout was added 
	if(strcmp(parsed[0], ti) == 0)
	{
		char num[100];
			strcpy(num, parsed[1]);
			int len = strlen(num);
			int dec = 0, i;
			for (i = 0; i<len; i++){
				dec = dec * 10 + (num[i] - '0'); // makes the second string an int to be used for alarm
			}
			char input[100];
			for(int l = 2; l < get_size(parsed); l++)
			{
				strcpy(input, parsed[l]);
			}
			
			pid_t pid;
			pid = fork(); //creates another process where alarm is ran
			int stat;
			if(pid == 0){
				alarm(dec);
				run_commands(input);
				/*for(int i = 0; i < 1000000000000000000; i++) used to test timeout 
				{
					i = i * i; 
				}*/
				alarm(0);
				_exit(0);
			}
		else
			wait(&stat); // will wait for child to exit as to not create a zombie 
	}
	
	
	else
		run_commands(line); // if no timeout was added
}while( status != 1);
  
}