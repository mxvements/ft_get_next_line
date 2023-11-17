<div align="center">
    <img src="https://img.shields.io/badge/status-finished-success?color=00ABAD&style=flat-square" />
    <img src="https://img.shields.io/badge/started-04%20%2F%2011%20%2F%202023-success?color=00ABAD&style=flat-square" />
    <img src="https://img.shields.io/badge/score-125%20%2F%20100-success?color=00ABAD&style=flat-square" />
    <img src="https://img.shields.io/github/languages/top/mxvements/ft_get_next_line?color=00ABAD&style=flat-square" />
    <img src="https://img.shields.io/github/last-commit/mxvements/ft_get_next_line?color=00ABAD&style=flat-square" />
    <br>
    <a href='https://www.linkedin.com/in/luciami' target="_blank"><img alt='Linkedin' src='https://img.shields.io/badge/LinkedIn-100000?style=flat-square&logo=Linkedin&logoColor=white&labelColor=1323233&color=323233'/></a>
    <a href='https://profile.intra.42.fr/users/luciama2' target="_blank"><img alt='42' src='https://img.shields.io/badge/Madrid-100000?style=flat-square&logo=42&logoColor=white&labelColor=323233&color=323233'/></a>
    <br>
</div>

# ft_get_next_line
This project will not only allow you to add a very convenient function to your collection, but it will also make you learn a highly interesting new concept in C programming: static variables.

| Function name | get_next_line |
| ------------- | ------------- |
| Prototype | char +get_next_line(int fd) |
| Turn in files | get_next_line.c, get_next_line_utils.c, get_next_line.h |
| Parameters | fd: the file descriptor to read from |
| Return value | Read Line: correct behaviour, NULL: there is nothing else to read, or an error occurred |
| External functs. | read, malloc, free |
| Description | wirte a function that returns a line read from a file descriptor |

* Mandatory part:
	- Repeated calls (e.g., using a loop) to your get_next_line() function should let you read the text file pointed to by the file descriptor, one line at a time.
	- Your function should return the line that was read .If there is nothing else to read or if an error occurred, it should return NULL.
	- Make sure that your function works as expected both when reading a file and when reading from the standard input.
	- Please note that the returned line should include the terminating \n character, except if the end of file was reached and does not end with a \n character.
	- Your header file get_next_line.h must at least contain the prototype of the get_next_line() function.
	- Add all the helper functions you need in the get_next_line_utils.c file.
	- Because you will to read files in get_next_line(), add this option to your compiler call: -D BUFFER_SIZE=n, It will define the buffer size for read(), The buffer size value will be mmodified by your peer-evaluators and the Moulinette in order to rest your code.
	- You will compile your code as follows (a buffer size of 42 is used as an example): cc -Wall -Wextra -Werror -D BUFFER SIZE=42 <files>.c
	- We consider that get_next_line() has an undefined behaviour if the files pointed to by the file descriptor changed size since the last call whereas read() didnt reach the end of file.
	- We also consider that get_next_line() has an undefined behavior when reading a binary file. However, you can implement a logical way to handle this behavior if you want to.

* Forbidden:
	- You are not allowed to use your libft in this project
	- lseek() is forbidden
	- Global variables are forbidden

* Bonus part:
	- Develop get_next_line() using only one static variable.
	- Your get_next_line() can manage multiple file descriptors at the same time. For example, if you can read from the file descriptors 3, 4 and 4, you should be able o read from a different fd per call without losing the reading thread of each file descriptor or returning a line from another fd.

# How to use

1 - Clone the repository
```
git@github.com:mxvements/ft_get_next_line.git
```

2 - Compilation

This project does not include a Makefile, in order to compile you should check the main.c file to see what .txt file you're reading. For compile, run the following, and use the BUFFER_SIZE size you prefer, sin it's casted as an int, the max amount of memory that can be used is (2147483647 - 1)
```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

3 - To incluide it in your code, include the header
```
#include "get_next_line.h"
```

# Notes

## Note on the file descriptors
File descritpors (*fd*) are non-negative ints that act as an abstract handle to 'Files' or I/O resources (like pipes, sockets or data streams). These descritors help us interact with these I/O resources and make working with them very easy. The I/O system is visible to a user process as a stream of bytes (I/O stream). A unix process uses descritors (small unsigned ints) to refer to I/O streams. The system calls related to the I/O operations take a descritpr as an argument.

Valid file descriptor ranges from 0 to OPEN_MAX on limits.h. Kernel assigns descriptors for std input (0), ouput (1), and error (2) on the file descritor table (system-wide table of files opened by all processes). If a file open is not successful, fd return -1.

- To interact wit files in C, we use functions llike open (man 2 open) which return aa file descriptor. The fd is then used in subsequent operations tto read from or write to the file.
- Once a file is open, we use read and write function to use the fd to specify the file or I/O resource.
- After we're done using a file or I/O resource, it's important to close it using close function.

## Notes on object-like macros

An object-like macro is a simple identifier which will be replaced by a code fragment. It is called object-like beacuse it looks like a data object in code that uses it. They are most commonly used to give symbolic name to numeric constants.

You create macros with the `#define` directive, followed by the name of the macro and then the token sequence it should be an abbreviation for, which is variously referred to as the macro's body, expansion or replacement list. For example,
 
 ```C
#define BUFFER_SIZE 1024 //defining BUFFER_SIZE macro as an abbreviation for the token 1024
```
```C
 foo = (char *) malloc (BUFFER_SIZE) //C preprocessor will recoginze and expand the macro BUFFER_SIZE
 foo = (char *) malloc (1024) //C preprocessor interpretation
 ```
source: [https://gcc.gnu.org/onlinedocs/cpp/Object-like-Macros.html] 

## Notes on static variables

The `static` keyword is used on variables or functions to determine the visibility inside files or functions. In this project, the focus on using `static vairables`.
 - For global variables, `static` is used to declare a var at the file scope (internal linkage), it limtis its visibility if thar var to the file where it's declared. The var cannot be accesed from other files using the `extern` keyword.
 - When `static` is used to declare a var inside a function, it changed the storage duration of that variable. Instead of being allocated on the stack and having a local lifetime, the variable is allocated in the data segment of the program, giving a lifetime throughout the entire program exection. The variabl retains its value between function calls.

 # General schema of the code
 1 - the main structre of the code consists on:

* read the file and store the content read on a static (char *) variable, a stash, we are going to update everytime we read the file
* when a newline is found, save the first line read on a (char *) variable, the line we need to return on the get_next_line function
* delete the first line on the stash to update it

2 - in order to know when to stop reading, and manage the end of file, my solution uses a structure that allocates:

* (char *)stash, the pointer to the joined strings of the former stash and the new read buffer
* (int) new line index, to know when a complete line is found
* (int) bytes read on the last read() call, when is smaller than the BUFFER_SIZE provided by the macro, then we've reached the end of file
* (int) string len, length of stash, to know the length of the last line o a file, when no newline is needed

```C
typedef struct stash
{
	int		stlen;
	int		nwline_i;
	ssize_t	readbytes;
	char	*stash;
}	t_stash;
```

### Bear in mind...

I'm aware that more efficient code can be implemented (e.g only getting the length of the stash when initizalizing the length of the line to be returned), this is the code I submitted to the vogsphere.

Also, the bonus code does not match the main code precisely because I wanted to do some last minute improvements.

## gnl_schema

General schema of the code without the protection of variables and mallocs, and w/o all axiliary functions:

1 - get_next_line(), which calls gnl_update_struct() and gnl_get_line()
```C
char	*get_next_line(int fd)
{	
	static t_stash	s_stash;
	char			*line;

	//protection of fd and BUFFER_SIZE, provided in compilation
	while (s_stash.nwline_i == 0)
	{
		gnl_update_struct(fd, &s_stash);
		//protection of s_stash.stash, to handle errors on gnl_update_struct()
		if (s_stash.readbytes < BUFFER_SIZE)
			break ;
			//break loop when newline found or reached the end of file
			//it could also be chequed when s_stash.stlen == 0, checking the readbytes we avoid the last read call
	}
	line = gnl_get_line(&s_stash);
	//after getting the line, we need to update the struct 
	//if stash.stlen == 0 we've reached the end of file, so we need to free s_stash.stash at the end
	return (line);
}
```
2.1 - gnl_update_struct()
```C
void	gnl_update_struct(int fd, t_stash *s_stash)
{
	s_stash->stash = gnl_read_file(fd, s_stash);//update the char *stash reading the file, use strjoin when stash is not empty. When calling this function, the s_stash.readbytes will be updated.
	//protection of s_stash.stash, to handle errors on the read function
	s_stash->nwline_i = gnl_strchr(s_stash->stash, '\n'); //is there a newline?
	s_stash->stlen = gnl_strlen(s_stash->stash); //stash len, useful for the end of file
	return ;
}
```

2.2 - gnl_get_line()
```C
char	*gnl_get_line(t_stash *s_stash)
{
	char	*line;
	int		linelen;

	//setting the length of the line we need to return, if it's not the end of file, then we set the index of the newline + 1 
	if (s_stash->nwline_i != 0)
		linelen = (s_stash->nwline_i) + 1;
	else
		linelen = s_stash->stlen;
	line = gnl_save_first_line(s_stash, linelen);
	//protection of line to handle errors on gnl_save_first_line()
	s_stash->stash = gnl_delete_first_line(s_stash, linelen);//memmove from stash[i + linelen] to stash[i], setting remaining memory to null
	return (line);
}
```

# Other

## Norminete
At 42 School, it is expected that almost every project is written in accordance with the Norm, which is the coding standard of the school.

<a href="https://github.com/42School/norminette">
<a>Norminette's repository</a>

```
- No for, do...while, switch, case, goto, ternary operators and variable-length arrays are allowed
- Each function must be a maximum of 25 lines, not counting the function's curly brackets
- Each line must be at most 80 columns wide, comments included
- A function can take 4 named parameters maximum
- No assigns and declarations in the same line (unless static or const)
- You can't declare more than 5 variables per function
- ...
```
## Aknowledgments
- [Luiz-Pastor](https://github.com/Luiz-Pastor/get_next_line) helped me understand what gnl needed to do at the start. 

# License
[MIT License](https://github.com/mxvements/ft_license/blob/main/LICENSE.txt)