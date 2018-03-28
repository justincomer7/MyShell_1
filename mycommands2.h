#define DELIM " \t\r\n\a"
#define BUFF_FOR_GREP 100
#define BUFFSIZE 64
#include <grp.h>
#include <pwd.h>
#include <locale.h>
#include <time.h>
#include <langinfo.h>
#include <sys/wait.h>

void welcome()
{
	printf("***************************************\n");
	printf("**Welcome to Justin and Dylan's Shell**\n");
	printf("***************************************\n\n");
}
char *read_line()
{
	
	char *line;
	line = (char *)malloc(BUFFSIZE * sizeof(char));
	
	size_t buffsize = BUFFSIZE;
	getline(&line, &buffsize, stdin);
	return line;
}

void env_print(char **envp)
{
	for(char **env = envp; *env!= 0; env++){
				char *thisEnv = *env;
				printf("%s\n", thisEnv);
	}
}

void time_out(int limit, char *command)
{
	pid_t pid;
	pid = fork();
	int status;
	if(pid == 0){
		alarm(limit);
		for(int i = 0; i < 1000000000000000000; i++)
		{
			i = i * i; 
		}
		alarm(0);
		exit(0);
	}
	else
		wait(&status);
}

char **parser(char *line)
{
	int position = 0;
	char **tokens = malloc(BUFFSIZE * sizeof(char*));
	char *token;

	if(!tokens)
	{
		fprintf(stderr, "allocation error\n");
		exit(0);
	}
	token = strtok(line, DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		token = strtok(NULL, DELIM);
	}

	tokens[position] = NULL;
	return tokens;
}
