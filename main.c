#include "tokens.h"

int	main(void)
{
	char		*line;
	t_token		*tokens;
	int 		i = 0;
	pid_t		pid;
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
		line = readline("$: ");
		tokens = tokenize_line(line);
		print_tokens(tokens);
		free_tokens(tokens);
		free(line);
	}
}