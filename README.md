# cash
The ca$h shell is one after bash.

## TODO for rev 0.2
* Use _s copy functions
* Refactor parser
* Re-think function seperation of source and main file

## Overview
The shell we made offers very basic functionality. It's methodology is as follows:

### Prompt and take input
The input relies on a special ```enum rflag``` which handles the extra credit condition that ```CTRL-D``` should act as a new line.
The only time the input buffer is submitted for parsing is when the flag is set to ```DONE```.
If the size returned when complete is 0, then exit the program.

### Parse arguments
The parser is the most complicated part. It ignores whitespace and copies characters into a buffer provided for arguments.
Words are seperated by whitespace or the special ```<``` and ```>``` redirection characters.
If a redirect symbol is parsed, the next word becomes the file to be redirected.
The words are copied into either the buffer, the ```infile``` or the ```outfile```.

There are a number of problems that can occur when redirecting:
* Multiple redirects in or out
* No file given for redirection

These are all checked and if failed, the parser returns -1, otherwise it returns the number of arguments in the buffer.

### Try fork and execute
A child process is spawned to execute the buffer provided by the parser, which will have the executable file with its arguments in an eargv buffer.
If either the ```infile``` or the ```outfile``` has been set, that means there has been a redirection,
A function is called that closes STDIN or STDOUT (with either QUASH or APPEND depending on flag).
If there is a problem opening the redirection files, the child process gives an error message and exits.

### Try built-in commands
The parent process waits and if execution fails in some way, it tries its built-in commands.
If those fail as well, an error message is printed, but the shell continues to execute.

### Clean up
The ```infile``` and ```outfile``` for redirection are cleared.
The buffers filled by parsing are also cleared.
These are all dynamically allocated so we must use ```free()```

## Assumptions
We knew that parsing would be the hardest part of the assignment. 
It was easy ignore whitespace but once redirection came in, the parser got a lot more complicated.
Using the built-in functions was very simple and intuitive.
We were also worried that not being able to use ```printf()``` and ```scanf()``` was going to be difficult but the system calls were easy to understand and all we needed.

## Design decisions
The hardest part of design came with how to handle errors and multiple data being returned.
The biggest example of this was the parse function. The original design was simple and translated the input buffer into an array of strings by seperating words by whitespace.
As redirection came in, the parser needed to handle not only setting the in and out files, but communicating errors with redirection.
The parser could be broken up into different sections to be more organized and focused.
Introducing a more clear error system would make the program clearer, but we figured it was more important to get it functioning before worrying about detailed error handling.

It was also import that memory not leak, so whenever a function is calling malloc, there is a clean up functional calling free.

## Summary
We had never thought about what the components of a shell were or dealt with as low-level system calls as those in ```unistd.h```.
A lot of the issues came in the form of off-by-one errors.
It was neccessary to print out the contents of the buffer constantly to verify the correct data was being moved around.
The system calls were easy to understand, the most difficult part was managing the parsing of the input buffer and the error handling.

