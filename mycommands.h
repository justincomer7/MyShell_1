#define DELIM " \t\r\n\a"
#define BUFF_FOR_GREP 100
#define BUFFSIZE 64

void welcome()
{
	printf("*****************************\n");
	printf("**Welcome to Justin's Shell**\n");
	printf("*****************************\n\n");
}
char *read_line()
{
	
	char *line;
	line = (char *)malloc(BUFFSIZE * sizeof(char));
	
	size_t buffsize = BUFFSIZE;
	getline(&line, &buffsize, stdin);
	return line;
}

void list_files()
{
	struct dirent *de;
	
	DIR *dr = opendir(".");

	if(dr == NULL){printf("Error\n");}

	while ((de = readdir(dr)) != NULL)
		printf("%s ", de->d_name);
	printf("\n");
	closedir(dr);
}

void list_long()
{
	char buf[BUFFSIZE];
	struct dirent *de, *dl; 
	struct stat mystat;
	DIR *dr = opendir(".");
	if(dr == NULL){printf("Error\n");}

	int num = 0;
	while((dl = readdir(dr)) != NULL)
		num++;
	
	printf("Total: %d\n", num);
	closedir(dr);
	DIR *ds = opendir(".");
	while((de = readdir(ds)) != NULL)
	{
		sprintf(buf, "%s", de->d_name);
		stat(buf, &mystat);
		printf((S_ISDIR(mystat.st_mode)) ? "d" : "-");
		printf((mystat.st_mode & S_IRUSR) ? "r" : "-");
		printf((mystat.st_mode & S_IWUSR) ? "w" : "-");
		printf((mystat.st_mode & S_IXUSR) ? "x" : "-");
		printf((mystat.st_mode & S_IRGRP) ? "r" : "-");
		printf((mystat.st_mode & S_IWGRP) ? "w" : "-");
		printf((mystat.st_mode & S_IXGRP) ? "x" : "-");
		printf((mystat.st_mode & S_IROTH) ? "r" : "-");	
		printf((mystat.st_mode & S_IWOTH) ? "w" : "-");
		printf((mystat.st_mode & S_IXOTH) ? "x " : "- ");
		printf("%zu", mystat.st_size);
		printf(" %s\n", de->d_name);
	}
	closedir(dr);
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

void print_file(char *file1)
{
	char ch;
	FILE *source;
	source = fopen(file1, "r");
	if(source != NULL)
	{	
		while((ch=fgetc(source))!=EOF)
			fputc(ch, stdout);
	}
	else{
		printf("cat: ");
		printf("%s", file1); 
		printf(": No such file or directory\n");
	}
}

void copy_file(char *file1, char *file2)
{
	char ch;
	FILE *source, *target;

	source = fopen(file1, "r");
	if(source != NULL)
		target = fopen(file2, "w");

	if(source != NULL && target != NULL)
	{
		while((ch=fgetc(source))!=EOF)
			fputc(ch, target);
	
	printf("File Copied\n");
	}	
	else 
		printf("File error\n");
}

int find(char *file1, char *find)
{
	FILE *fp; 
	char buf[BUFF_FOR_GREP];
	char *newline;

	fp = fopen(file1, "r");
	if(fp == NULL)
		printf("Error\n");
	else
	{
		while (fgets(buf, BUFF_FOR_GREP, fp) != NULL)
		{
			if(newline = strchr(buf, '\n'))
				*newline = '\0';
			if(strstr(buf, find) != NULL)
				printf("%s\n", buf);
		}		
	}
}
