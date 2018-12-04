//
//  nesh.c
//  NESH
//
//  Created by Nehir Poyraz on 23.12.2017.
//  Copyright © 2017 Nehir Poyraz. All rights reserved.
//
#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <string.h>
#include<sys/wait.h>
#include <libgen.h>
#include "nesh.h"
#define NESH_TOK_BUFSIZE 256
#define NESH_TOK_DELIM " \t\r\n\a"
char *extension_str[] = {
	"help",
	"nman",
	"whereami",
	"cd",
	"nsort",
	"play",
	"convert",
	"exit"
	
};

int (*extension_func[]) (char **) = {
	&nesh_help,
	&nesh_nman,
	&nesh_whereami,
	&nesh_cd,
	&nesh_nsort,
	&nesh_play,
	&nesh_convert,
	&nesh_exit
};

int nesh_num_extensions() {
	return sizeof(extension_str) / sizeof(char *);
}

int nesh_help(char **args)
{
	int i;
	printf("\nNehir's Shell NESH\n\n");
	printf("Type program names and arguments, and hit enter.\n\n");
	printf("The following are extensions:\n");
	
	for (i = 0; i < nesh_num_extensions(); i++) {
		printf("\t%s\n", extension_str[i]);
	}
	printf("\nUse the nman command for information on nesh extensions.\n\n");
	printf("Use the man command for information on other programs.\n\n");
	
	return 1;
}

int nesh_whereami(char **args) {
	char* argsv[] = {"bash" , "-c" , "pwd", NULL};
	args = argsv;
	return nesh_launch(args);
}

int nman_whereami(char **args) {
	printf("\nWHEREAMI\t\t\tNESH Extension Commands Manual\t\t\tWHEREAMI\n\n");
	printf("NAME\n\twhereami -- display working directory name\n\n");
	printf("SYNOPSIS\n\tnsort [-ad option] [file]\n\n");
	printf("DESCRIPTION\n");
	printf("\nThe whereami utility writes the absolute pathname of the current working directory to the standard output.\n\n");
	printf("The command line options are as follows:\n\n");
	printf("-L\n\tDisplay the logical current working directory.\n\n");
	printf("-P\n\tDisplay the physical current working directory (all symbolic links resolved).\n\n");
	printf("If no options are specified, the -L option is assumed.\n\n");
	printf("Use the nman command for information on nesh extensions.\n\n");
	printf("Use the man command for information on other programs.\n\n");
	return 1;
}


int nesh_cd(char **args) {
	if (args[1] == NULL) {
		fprintf(stderr, "nesh: expected argument to \"cd\"\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("nesh");
		}
	}
	return 1;
}

int nman_cd(char **args) {
	char *argsv[] = {"bash", "man", "cd", NULL};
	args = argsv;
	return nesh_launch(args);
}


int nesh_nman(char **args) {
	if (args[1] == NULL) {
		fprintf(stderr, "nesh: expected argument to \"nman\"\n");
	}
	else if (strcmp(args[1], "help") == 0) {
		fprintf(stderr,"no manual entry for help\n");
	}
	else if (strcmp(args[1], "nman") == 0) {
		return nman_nman(args);
	}
	else if (strcmp(args[1], "whereami") == 0) {
		return nman_whereami(args);
	}
	else if (strcmp(args[1], "cd") == 0) {
		return nman_cd(args);
	}
	else if (strcmp(args[1], "nsort") == 0) {
		return nman_nsort(args);
	}
	else if (strcmp(args[1], "play") == 0) {
		return nman_play(args);
	}
	else if (strcmp(args[1], "convert") == 0) {
		return nman_convert(args);
	}
	else if (strcmp(args[1], "exit") == 0) {
		return nman_exit(args);
	}
	
	else {
		fprintf(stderr, "nesh: nman %s command not found\n", args[1]);
	}
	return 1;
}

int nman_nman(char **args) {
	printf("\nNMAN\t\t\tNESH Extension Commands Manual\t\t\tNMAN\n\n");
	printf("NAME\n\tnman -- display the nesh extension command manuals\n\n");
	printf("SYNOPSIS\n\tman name\n\n");
	printf("DESCRIPTION\n");
	printf("\nnman display the nesh extension command manuals. name is normally the name of the manual page, which is typically the name of a command\n\n");

	printf("Use the nman command for information on nesh extensions.\n\n");
	printf("Use the man command for information on other programs.\n\n");
	return 1;
}


int nesh_nsort(char **args) {
	
	if (args[1] == NULL) {
		fprintf(stderr, "nesh: expected argument to sort\n");
		fprintf(stderr, "usage: nsort [-a] [-d] source_file\n");
	}
	else{
		if (strcmp(args[1], "-a") != 0 && strcmp(args[1], "-d") != 0) {
			char* argsv[] = {"bash","./prog/sort.sh", args[1], NULL};
			args = argsv;
		}
		else {
			char* argsv[] = {"bash","./prog/sort.sh", args[1], args[2], NULL};
			args = argsv;
		}
		return nesh_launch(args);
	}
	
	return 1;
}

int nman_nsort(char **args) {
	printf("\nNSORT\t\t\tNESH Extension Commands Manual\t\t\tNSORT\n\n");
	printf("NAME\n\tnsort -- sort numeric records of text files\n\n");
	printf("SYNOPSIS\n\tnsort [-ad option] file\n\n");
	printf("DESCRIPTION\n");
	printf("\nThe nsort utility sorts text files containing only numeric values. Radix sort algorithm is used in implementation.\n\n");
	printf("The command line options are as follows:\n\n");
	printf("-a\n\tPerform sorting in ascending order\n\n");
	printf("-d\n\tPerform sorting in descending order\n\n");
	printf("If no options are specified, the -a option is assumed.\n\n");
	printf("Use nman command for information on nesh extensions.\n\n");
	printf("Use the man command for information on other programs.\n\n");
	return 1;
}

int nesh_play(char **args) {
	if (args[1] == NULL) {
		fprintf(stderr, "nesh: expected argument to play\n");
		fprintf(stderr, "usage: play --guess \n");
	}
	
	else if (strcmp(args[1], "--guess") != 0) {
		fprintf(stderr, "usage: play --guess \n");
	}
	else {
		char* argsv[] = {"bash","./prog/play.sh", NULL};
		args = argsv;
		return nesh_launch(args);
	}
	return 1;
}

int nman_play(char **args) {
	printf("\nPLAY\t\t\tNESH Extension Commands Manual\t\t\tPLAY\n\n");
	printf("NAME\n\tplay -- play various simple games\n\n");
	printf("SYNOPSIS\n\tplay [game option]\n\n");
	printf("DESCRIPTION\n");
	printf("\nplay utility provides entertainment in a terminal environment. Although it now has only one, new options are on the way.\n\n");
	printf("The command line options are as follows:\n\n");
	printf("--guess Play guessing game\n\n");
	printf("Use the nman command for information on nesh extensions.\n\n");
	printf("Use the man command for information on other programs.\n\n");
	return 1;
}

int nesh_convert(char **args) {
	char* argsv[] = {"bash" , "./prog/convert.sh", NULL};
	args = argsv;
	return nesh_launch(args);
}

int nman_convert(char **args) {
	printf("\nCONVERT\t\t\tNESH Extension Commands Manual\t\t\tCONVERT\n\n");
	printf("NAME\n\tconvert -- multidirectional converter for number systems\n\n");
	printf("SYNOPSIS\n\tconvert\n\n");
	printf("DESCRIPTION\n");
	printf("\nconvert utility helps you calculate binary, octal, decimal, or hexadecimal values from a binary, octal, decimal, or hexadecimal number \n\n");
	printf("Command does not take any command line options. Navigation occurs within the program.\n\n");
	printf("Use the nman command for information on nesh extensions.\n\n");
	printf("Use the man command for information on other programs.\n\n");
	return 1;
}

int nesh_exit(char **args)
{
	return 0;
}

int nman_exit(char **args) {
	char *argsv[] = {"bash", "man", "exit", NULL};
	args = argsv;
	return nesh_launch(args);
}


int nesh_launch(char **args)
{
	pid_t pid;
	int status;
	
	pid = fork();
	if (pid == 0) {
		// Child process
		if (execvp(args[0], args) == -1) {
			perror("nesh: error executing command");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		// Error forking
		perror("nesh: error forking");
	} else {
		// Parent process
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	
	return 1;
}
int nesh_execute(char **args)
{
	int i;
	if (args[0] == NULL) {
		// An empty command was entered.
		return 1;
	}
	
	for (i = 0; i < nesh_num_extensions(); i++) {
		if (strcmp(args[0], extension_str[i]) == 0) {
			return (*extension_func[i])(args);
		}
	}
	
	return nesh_launch(args);
}


char *nesh_read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0; // have getline allocate a buffer for us
	getline(&line, &bufsize, stdin);
	return line;
}

char **nesh_split_line(char *line)
{
	int bufsize = NESH_TOK_BUFSIZE, position = 0;
	char **tokens = (char**)malloc(bufsize * sizeof(char*));
	char *token;
	
	if (!tokens) {
		fprintf(stderr, "nesh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	
	token = strtok(line, NESH_TOK_DELIM);
	while (token != NULL) {
		if(isWord(token)) {
			tokens[position] = token;
			position++;
			
			if (position >= bufsize) {
				bufsize += NESH_TOK_BUFSIZE;
				tokens = realloc(tokens, bufsize * sizeof(char*));
				if (!tokens) {
					fprintf(stderr, "nesh: allocation error\n");
					exit(EXIT_FAILURE);
				}
			}
			
			token = strtok(NULL, NESH_TOK_DELIM);
			
		}
		else
			break;
	}
	tokens[position] = NULL;
	return tokens;
}

bool isWord (char *token) {
	if(strcmp(token, "|") != 0 && strcmp(token, ">") != 0 && strcmp(token, ">>") != 0 && strcmp(token, "<") != 0 && strcmp(token, "<<") != 0)
		return true;
	else
		return false;
}

bool isPipe (char *token) {
	if(strcmp(token, "|") == 0)
		return true;
	else
		return false;
}

void nesh_loop(void)
{
	char *line;
	char **args;
	int status;
	char host[64];
	char path[256];
    nesh_execute(nesh_split_line("help"));
	do {
		gethostname(host, 64);
		getwd(path);
		printf("%s@%s:%s » ", getlogin(), host, basename(path));
		line = nesh_read_line();
		args = nesh_split_line(line);
		status = nesh_execute(args);
		free(line);
		free(args);
	} while (status);
}




