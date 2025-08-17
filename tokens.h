#ifndef TOKENS_H
# define TOKENS_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <strings.h>
# include <wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef enum	e_token_type
{
	WORD,
	PIPE,
	AND_IF,
	OR_IF,
	ASSIGNMENT,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC,
	DELIMITER,
	L_PARENTHESES,
	R_PARENTHESES,
	NONE,
	TOK_EOF

}	t_token_type;

typedef struct	e_lexer_state
{
	bool	in_token;
	bool	in_single_quote;
	bool	in_double_quote;
}	t_lexer_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;


#endif