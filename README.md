# Linux-shell-in-C
Linux Command Interpreter (Shell) in C language

The shell will give a prompt for the user to type in a command, take the command, execute it, and then give the prompt back for the next command (i.e., actually give the functionality of a shell).
My program satifies the below conditions :

o Give a prompt (like the $ prompt you get in Linux) for the user to type in a command. The prompt should have the current working directory name (full path) followed by the “>” sign (for ex., /usr/home/agupta/temp> ).
o Implement the following commands as builtin commands:
  cd <dir> : changes the directory to "dir"
  pwd : prints the current directory
  mkdir <dir> : creates a directory called "dir"
  rmdir <dir> : removes the directory called "dir"
  ls : lists the files in the current directory. It should support ls both without any
option and with the option “-l”
  cp <file1> <file2>: copies the content of “file1” into “file2” only if the last
modification time of “file1” is more recent than that of “file2”. The filenames
may contain a full pathname. You can assume “file1” and “file2” are simple files
and not directories. No option of cp needs to be supported.
  exit : exits the shell

All calls should handle errors properly, with an informative error message. For example,
cp will fail if the user calling it does not have read permission on “file1”; the call should
print a proper error message. Look up the perror call.
These commands are called builtin commands since your shell program will have a
function corresponding to each of these commands to execute them; no new process will
be created to execute them. (Note that all these commands are not builtin commands in
the bash shell, but we will make them so in our shell).

o Any other command typed at the prompt should be executed as if it is the name of an
executable file. For example, typing "./a.out" should execute the file a.out. The file
should be executed after creating a new process and then exec'ing the file onto it. The
parent process should wait for the file to finish execution and then go on to read the next
command from the user. The command typed can have any number of command line
arguments. You can assume that the full pathname of the file to be executed will be
specified.

o Support background execution of commands. Normally when you type a command at
the shell prompt, the prompt does not return until the command is finished. For
background executions, the prompt returns immediately, the command continues
execution in the background. Typing an "&" at the end of a command (for ex., a.out&)
should make it execute in the background.

o Should be able to redirect the output of a program to a file using ">" and read the input
of a program from a file using <. For example, typing 
a.out > outfile
should send whatever was supposed to be displayed on the screen by a.out to the file outfile .
Similarly, typing 
a.out < infile 
should make a.out take the inputs from the file infile instead of the keyboard. You should support both input 
and output redirection in the same command.

o Should be able to redirect the output of one command to the input of another by using
the "|" symbol. For example, if there is a program a.out that writes a string abcde to
the display, and there is a program b.out that takes as input a string typed from the
keyboard, counts the number of characters in the string, an displays it, then typing 
a.out| b.out
at your shell prompt should display 5 (the output abcde from a.out was fed as
input to b.out, and 5, the number of characters in abcde, is printed). Use the pipe
command. You should support at least 2 levels of piping (for ex., a | b | c).
To run your shell, write another C program that will create a child process and call an
appropriate form of exec to run the program above from the linux shell. The parent process
simply waits for the child to finish (execute the "exit" command), after which it also exits.

When entering the commands, keep the following things in mind :
1. The command keywords should be of lower case ( like in the original shell )
2. There should be space between 2 words/symbols.
   Eg : a)  ./file1 &
        b)  ./f1 | ./f2 | ./f3  ( piping seqeunce )
3. Make sure you give the proper pathname of the file to be executed.






