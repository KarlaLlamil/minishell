CTRL_OPERATOR ::= '|'   |   CTRL_OPERATOR '&&' LINEBREAK  PIPELINE   |  CTRL_OPERATOR '||' LINEBREAK PIPELINE

WORD ::= (letter | digit | )
( sequence of alphanumeric characters or '_')

REDIRECTION ::= [fd]'<'   |   [fd] '>'['|'] WORD   
('>&' WORD | '&>' WORD) 

APPEND ::= [fd] '>>' WORD
(&>>WORD)

HERE_DOC ::= [fd] '<<' delimiter '\n'
						content
			delimiter '\n'

IO_REDIRECTION ::= REDIRECTION | APPEND | HERE_DOC

io_file          : '<'  filename
                 | '>'  filename
                 | '>>'	filename
                 | '<<' filename

ASSIGNMENT ::= VAR_NAME'='VAR_VALUE

VAR_NAME ::=  sequence of alphanumeric begin with a letter or '_'

SIMPLE_CMD ::= [IO_REDIRECTION] [ASSIGNMENT] WORD [WORD]* [IO_REDIRECTION]* 
After a SIMPLE_CMD there should always follow a [CONTROL_OPERATOR]

PIPELINE ::= SIMPLE_CMD '|' SIMPLE_CMD     |    PIPELINE '|' SIMPLE_CMD
			PIPE_SEQUENCE

PIPE_SEQUENCE ::= SIMPLE_CMD | PIPE_SEQUENCE '|' LINEBREAK SIMPLE_CMD

COMPOUND_COMMAND ::= SUBSHELL



LIST ::= PIPELINE '&&' PIPELINE | PIPELINE '||' PIPELINE 

SUBSHELL ::= '(' LIST ')'

The grammar symbols
Token

	WORD
	ASSIGNMENT_WORD
	NAME
	NEWLINE
	IO_NUMBER

Operators 

	AND_IF
	OR_IF

#In shell terminology, “clobber” refers to overwriting an existing file when redirecting output.

