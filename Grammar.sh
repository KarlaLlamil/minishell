CTRL_OPERATOR ::= '|'   |   '&&'    |     '||'   |     '\n'

WORD ::= sequence of alphanumeric characters or '_'

REDIRECTION ::= [fd]'<'   |   [fd] '>'['|'] WORD   
('>&' WORD | '&>' WORD) 

APPEND ::= [fd] '>>' WORD
(&>>WORD)

HERE_DOC ::= [fd] '<<' delimiter '\n'
						content
			delimiter '\n'

IO_REDIRECTION ::= REDIRECTION | APPEND | HERE_DOC

ASSIGNMENT ::= VAR_NAME'='VAR_VALUE

VAR_NAME ::=  sequence of alphanumeric begin with a letter or '_'

SIMPLE_CMD ::= [IO_REDIRECTION] [ASSIGNMENT] WORD [WORD]* [IO_REDIRECTION]* 
After a SIMPLE_CMD there should always follow a [CONTROL_OPERATOR]

PIPELINE ::= SIMPLE_CMD '|' SIMPLE_CMD     |    PIPELINE '|' SIMPLE_CMD

LIST ::= PIPELINE '&&' PIPELINE | PIPELINE '||' PIPELINE 

(LIST) excute the LIST in a subshell


TOKEN TYPE
#
IO_REDIRECTION (o por separado REDIRECTION APPEND HERE_DOC)
PIPE
'&&'
'||'
'('
')'


