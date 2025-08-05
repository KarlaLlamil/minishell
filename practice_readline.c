#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <strings.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

int	main(void)
{
	char		*line;
	int 		i;
	pid_t		pid;
	pid_t		pidls;
	int			statusls;
	int			status;
	extern char	**environ;
	char	*args[] = {"clear", NULL};
	char	*argsls[] = {"ls", NULL};

	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/clear",args,environ);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	while(i == 0)
	{
		line = readline("Prueba: ");
		if ( strcmp(line, "C") == 0)
		{
			i = 1;
			printf("You entered: \"%s\"\n", line);
			free(line);
		}
		else if (strcmp(line,"ls") == 0)
		{
			pidls = fork();
			if (pidls == 0)
			{
				execve("/usr/bin/ls",argsls,environ);
			}
			else
			{
				waitpid(pidls, &statusls, 0);
			}
		}
		else if (strcmp(line,"cd") == 0)
		{
			chdir("/home/karla/Documents/42_Cursus");
		}
		else
			printf("You entered: \"%s\"\n", line);



	}

    return 0;
}