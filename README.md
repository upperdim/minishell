## Description

Minishell is an operating system shell, providing a complete command line interface for the system. REPL-based command interpreter features lexical parsing, command tokenization, and execution. Written in C programming language from scratch with a self implemented C library (libft) using Unix system calls. Handled core process management using Unix system calls (fork, exec, wait), enabling execution of both builtin and external programs. 

## Main Features

- Pipeline execution (|) 
- I/O redirections (>, <, >>)
- Multi-process command chaining
- Environment variable expansion and
- Runtime modification of shell state
- Builtin shell commands (e.g., cd, exit, export)

## Code formatting

Code was formatted in compliance with the Norm format.

This is a highly unconventional format and does not reflect our own preference.

Some rules of the format:

- All source files must have the "42 header".
- Strict 80 column limit for all lines.
- Functions have a strict 25 line limit.
- Variables must be declared at the top of the functions (like C89 style).
- Functions can define at most 5 variables.
- No empty lines allowed inside the function body except right after the variable declaration.
- No comments allowed inside the function body.
- Functions can have at most 4 parameters.
- Maximum of 5 functions per file.

# Examples

- Redirections

	- Input `<`

		- Basic input

			```
			cat < file.txt
			```

		- Non-existent file

			```
			cat < does_not_exist.txt
			```

		- Input + args

			```
			wc -l < file.txt
			```

	- Output `>`

		- Basic overwrite

			```
			echo hello > out.txt
			cat out.txt
			```

		- Overwrite existing file

			```
			echo first > out.txt
			echo second > out.txt
			cat out.txt
			```
		- Command + output

			```
			ls > out.txt
			```


	- Append `>>`

		- Basic append

			```
			echo a >> out.txt
			echo b >> out.txt
			cat out.txt
			```

		- Mix overwrite + append

			```
			echo start > out.txt
			echo middle >> out.txt
			echo end >> out.txt
			cat out.txt
			```

	- Heredoc `<<`

		- Basic heredoc

			```
			cat << EOF
			hello
			world
			EOF
			```

		- Empty heredoc

			```
			cat << EOF
			EOF
			```

		- Multiple lines

			```
			cat << STOP
			one
			two
			three
			STOP
			```

	- Edge / bug-detection tests

		- No space cases

			```
			echo hi>file.txt
			cat<file.txt
			```

		- Multiple redirections

			```
			echo hello > a.txt > b.txt
			```

		- Mixed input/output

			```
			wc -l < file.txt > out.txt
			```
