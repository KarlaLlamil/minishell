#include <tokens.h>

bool is_ifs(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else
		return (false);
}

t_token_type is_operator(char *c)
{
	if (*c == '|' && *(c + 1) != '|')
		return (PIPE);
	else if (*c == '|' && *(c + 1) == '|')
		return(OR_IF);
	else if (c == '&'
	 || c == '(' || c == ')')
		return (true);
	else
		return (false);
}

t_token	get_token(char *start, char *line, int j)
{
	if (line[j])
}

t_token	*tokenize_lines(char *line)
{
	t_lexer_state	state;
	t_token			*tokens;
	char			*start_token;
	int				i;
	int				j;

	i = 0;
	j = 0;
	tokens = malloc(sizeof(t_token)*32);
	state = (t_lexer_state){};

	while (line[j] != '\0')
	{
		if (state.in_token == false && is_ifs(line[j]) == false && is_operator(&line[j]) == false)
		{
			state.in_token = true;
			start_token = &line[j];
		}
		else if (state.in_token == true && (is_ifs(line[j]) == true || is_operator(&line[j]) == true) )
			tokens[i] = get_token(start_token, line, j);
		if (line[j] == '"')
			state.in_double_quote = true;
		else if (line[j] == '\'')
			state.in_single_quote = true;
	}

}