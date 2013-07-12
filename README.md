![](https://raw.github.com/createch/ghettocli/master/gcli.png)

ghettocli
=========

A ghetto command line interpreter.

Usage
=====

./gcli [-v] [-f batchfile]
Or: ./gcli batchfile

-v: Print version
batchfile: Read commands from file

No arguments starts a shell and reads commands from stdin:

Built-in:
	LS, PWD, CD, ECHO, PAUSE, CLEAR, HELP, QUIT

Accepts executable files by absolute path or will search through the PATH environment variable.

Default execution is foreground, but may be placed in the background by appending a '&amp;'

Command history is maintained and can be found using the arrow up and down keys..

