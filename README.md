<div align="center">
    <img src="https://img.shields.io/badge/status-finished-success?color=00ABAD&style=flat-square" />
    <img src="https://img.shields.io/badge/started-04%20%2F%2011%20%2F%202023-success?color=00ABAD&style=flat-square" />
    <img src="https://img.shields.io/badge/score--%20%2F%20100-success?color=00ABAD&style=flat-square" />
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

# Notes

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