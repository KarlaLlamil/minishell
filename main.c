#include "tokens.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <strings.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include "Libft/libft.h"

int	main(void)
{
	char		*line;
	t_token		**tokens;
	int 		i = 0;
	pid_t		pid;
	int			status;
	extern char	**environ;
	char	*args[] = {"clear", NULL};

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
		lexer_destroy_tokens(tokens);
		free(line);
	}
}