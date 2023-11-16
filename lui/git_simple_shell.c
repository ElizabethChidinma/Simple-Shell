#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 * execute_command - Parse and execute a command
 * @command: The command to be executed
 */
void execute_command(char *command)
{
pid_t pid = fork();
char *args[MAX_INPUT_SIZE];
int arg_count = 0;

char *token = strtok(command, " \t\n");
while (token != NULL)
{
args[arg_count] = token;
arg_count++;
token = strtok(NULL, " \t\n");
}
args[arg_count] = NULL;

if (pid == -1)
{
perror("Fork failed");
}
else if (pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("Command not found");
exit(1);
}
}
else
{
int status;
waitpid(pid, &status, 0);
}
}

/**
 * main - Entry point for the simple shell program
 *
 * Return: return 0
 */
int main(void)
{
char input[MAX_INPUT_SIZE];

while (1)
{
printf("$ ");
if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
{
break;
}

if (strlen(input) > 1)
{
input[strlen(input) - 1] = '\0'; /* to remove a newline */
if (strcmp(input, "exit") == 0)
{
break;
}
else
{
execute_command(input);
}
}
}
return (0);
}
