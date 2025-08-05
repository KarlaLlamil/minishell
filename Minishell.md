Functions permited for the project:

readline ->        char *
       readline (const char *prompt);

       #include <stdio.h>
       #include <readline/readline.h>
       #include <readline/history.h>

The  line returned is allocated with malloc(3); the caller must
       free it when finished.  The line returned has  the  final  newline  re‐
       moved, so only the text of the line remains.
       
   If EOF is encountered while reading a line, and the line
       is  empty,  NULL is returned.  If an EOF is read with a non-empty line,
       it is treated as a newline.

[[Shell grammar]]
