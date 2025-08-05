Every process has a current working directory. This directory is where the search for all
relative pathnames starts (i.e., with all pathnames that do not begin with a slash). When
a user logs in to a UNIX system, the current working directory normally starts at the
directory specified by the sixth field in the /etc/passwd file — the user ’s home
directory. The current working directory is an attribute of a process; the home directory
is an attribute of a login name.

We can change the current working directory of the calling process by calling the
chdir or fchdir function.

```c
#include <unistd.h>
int chdir(const char *pathname);

```

The current working directory for the shell that executed the mycd program didn’t
change. This is a side effect of the way that the shell executes programs. Each program
is run in a separate process, so the current working directory of the shell is unaffected
by the call to chdir in the program. For this reason, the chdir function has to be
called directly from the shell, so the cd command is built into the shells.

What we need is a function that starts at the current working directory (dot) and
works its way up the directory hierarchy, using dot-dot to move up one level. At each
level, the function reads the directory entries until it finds the name that corresponds to
the i-node of the directory that it just came from. Repeating this procedure until the
root is encountered yields the entire absolute pathname of the current working
directory. Fortunately, a function already exists that does this work for us.

Note that chdir follows the symbolic link—as we expect it to, from Figure 4.17 — but
when it goes up the directory tree, getcwd has no idea when it hits the /var/spool
directory that it is pointed to by the symbolic link /usr/spool. This is a characteristic
of symbolic links.
The getcwd function is useful when we have an application that needs to return to
the location in the file system where it started out. We can save the starting location by
calling getcwd before we change our working directory. After we complete our
processing, we can pass the pathname obtained from getcwd to chdir to return to our
starting location in the file system.