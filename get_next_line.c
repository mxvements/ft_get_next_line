/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:00:55 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/09 22:45:05 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/** char *gnl_strjoin(char **s1, char **s2)
 * @brief Function to join two strings in a new string, using memory allocation.
 * This imlementation of strjoin, considers s1 the stash, which len we need to
 * calculate, and s2 the read buffer of the file, which len we already know
 * (it's BUFFER_SIZE). It also takes the pointer to each string (char **), to 
 * pass them by reference.
 * Error handling: malloc protection, reuturn NULL.
 * @param s1, char **, pointer to stash (char *)
 * @param s2, char **, pointer to buff (char *)
 * @return char*, char *, new string
 */
char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*temp;

	i = -1;
	j = -1;
	len = gnl_strlen(s1);
	temp = (char *)malloc(sizeof(char) + (BUFFER_SIZE + len + 1));
	if (!(temp))
		return (NULL);
	while (s1[++i] != '\0')
		temp[i] = s1[i];
	while (s2[++j] != '\0')
		temp[i + j] = s2[j];
	temp[i + j] = '\0';
	return (temp);
}

/** char *gnl_read_file(int fd, t_stash *s_stash)
 * @brief Function to read the file from which to get the line.
 * On the first read (stash empty):
 * 		returns a string copied from the buffer string
 * In case the stash is not empty:
 * 		returns a string that concatenates the existing stash and the buffer
 *		(freeing the existing stash before return)
 * Error handling:
 * 		Malloc protection on the buffer string for the file read
 * 		Malloc protection on temp string when stash is null
 * 		In case read error, returns NULL and free stash and buff
 *		In case read = 0 bytes or reads only a null, free buff and return
 *		existing stash
 * @param fd, file descriptor of the file to read
 * @param s_stash, pointer to the static struct
 * @return char*, returns the joined/copied string
 */
char	*gnl_read_file(int fd, t_stash *s_stash)
{
	char	*buff;
	char	*temp;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (free(s_stash->stash), NULL);
	s_stash->readbytes = read(fd, buff, BUFFER_SIZE);
	if (s_stash->readbytes < 0)
		return (free(buff), free(s_stash->stash), buff = NULL, NULL);
	if (s_stash->readbytes == 0 || *buff == '\0')
		return (free(buff), buff = NULL, s_stash->stash);
	buff[s_stash->readbytes] = '\0';
	if (!(s_stash->stash))
		return (buff);
	temp = gnl_strjoin(s_stash->stash, buff);
	free(s_stash->stash);
	return (free(buff), buff = NULL, temp);
}

/** void gnl_update_struct(int fd, t_stash *stash)
 * @brief Function to update the static struct which contains:
 * - char * stash, withlll the remaining data of the file after returning the 1st
 * line
 * - stlen, stash length
 * - nwline_i, line length after '\n'
 * - readbytes, amount of bytes read, if < BUFFER_SIZE, reached end of file
 * Error handling:
 * 		if s_stash.stash is null, returns null
 * @param fd 
 * @param s_stash 
 */
void	gnl_update_struct(int fd, t_stash *s_stash)
{
	s_stash->stash = gnl_read_file(fd, s_stash);
	if (!s_stash->stash)
		return ;
	s_stash->nwline_i = gnl_strchr(s_stash->stash, '\n');
	s_stash->stlen = gnl_strlen(s_stash->stash);
	return ;
}

/** char *get_next_line(int fd)
 * @brief Get the next line from a file (fd).
 * When there is a newline on the stash
 *		get the first line on the stash and update it
 * When there is not newline
 * 		update the struct and read the file to update the stash until there is
 * 		a newline
 * Error handling:
 *		fd and BUFFER_SIZE protected
 * @param fd, file descriptor of the file to read
 * @return char*, line to return
 */
char	*get_next_line(int fd)
{	
	static t_stash	s_stash;
	char			*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	while (s_stash.nwline_i == 0)
	{
		gnl_update_struct(fd, &s_stash);
		if (!s_stash.stash)
			return (NULL);
		if (s_stash.readbytes < BUFFER_SIZE)
			break ;
	}
	line = gnl_get_line(&s_stash);
	s_stash.nwline_i = gnl_strchr(s_stash.stash, '\n');
	s_stash.stlen = gnl_strlen(s_stash.stash);
	if (s_stash.stlen == 0)
	{
		free(s_stash.stash);
		s_stash.stash = NULL;
	}
	return (line);
}
