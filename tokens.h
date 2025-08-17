#ifndef TOKENS_H
# define TOKENS_H


# include <stdbool.h>
# include <stddef.h>

typedef enum	e_lex_exit_status
{
	LEX_OK,
	LEX_ERR_ALLOC,
	LEX_ERR_UNKNOWN_TOKEN,
	LEX_ERR_UNCLOSED_QUOTE,
	LEX_ERR_UNCLOSED_PAREN,
	LEX_ERR_UNEXPECTED_EOF,

}	t_lex_exit_status;

typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND_IF,
	TOKEN_OR_IF,
	TOKEN_ASSIGNMENT,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HERE_DOC,
	TOKEN_DELIMITER,
	TOKEN_L_PAREN,
	TOKEN_R_PAREN,
	TOKEN_UNKNOWN,
	TOKEN_EOF

}	t_token_type;

typedef enum	e_lexer_state
{
	LEX_DEFAULT,
	LEX_IN_SQUOTES,
	LEX_IN_DQUOTES,
	LEX_IN_OPERATOR,
	LEX_IN_WORD

}	t_lexer_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

/* **tokens -> array of tokens fixed size allocated
 size -> total number of tokens that can hold
 count -> current number of tokens 
 pos-> current position in the line*/

typedef struct	s_arg_lexer
{
	t_lexer_state		state;
	t_token				**tokens;
	char				*start_word;
	t_token_type		previous_token;
	char				*line;
	size_t				pos;
	size_t				size;
	size_t				count;
	t_lex_exit_status	status;

}	t_arg_lexer;

t_token	**tokenize_line(char	*line);
void	lexer_init(t_arg_lexer	*lexer, char *line);
void	lexer_make_token(t_arg_lexer *lexer);
void	lexer_default_state(t_arg_lexer *lexer);
void	lexer_squote_state(t_arg_lexer *lexer);
void	lexer_dquote_state(t_arg_lexer *lexer);
void	lexer_operator_state(t_arg_lexer *lexer);
void	lexer_word_state(t_arg_lexer *lexer);
void	lexer_handle_error(t_arg_lexer *lexer);
void	lexer_destroy_tokens(t_token **tokens);

#endif