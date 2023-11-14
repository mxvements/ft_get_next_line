/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:19:21 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/09 22:44:59 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/** int gnl_strlen(char *s)
 * @brief Function to get the length of a string. Iterates until it finds a \0
 * @param s, string to get the length
 * @return int, length of the str
 */
int	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

/** int gnl_strchr(char *stash, char c)
 * @brief Function to find the 1st occurrence of a char c in string stash.
 * Used to find the first '\n' on the stash. Returns the lgenth of the line,
 * (index + 1)
 * Error handling
 * 		char *stash protected
 * 		returns 0 when c not present
 * @param stash, char *, string to read
 * @param c, char to find
 * @return int, (index + 1) when find c, 0 when it's not present
 */
int	gnl_strchr(char *stash, char c)
{
	size_t	i;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i] != '\0')
	{
		if (stash[i] == c)
			return (++i);
		i++;
	}
	return (0);
}

/** char *gnl_save_first_line(t_stash *s_stash, int linelen)
 * @brief Function to return the first line on the s_stash.stash.
 * Uses malloc and linelen to allocate the space for the new string, line.
 * Error handling:
 * 		Malloc protection on char *line.
 *		When s_stash.stash is null, returns nulll
 * @param s_stash, pointer to the static struct which has the char *stash
 * @param linelen, length of line to be returned
 * @return char*, 1st line on stash
 */
char	*gnl_save_first_line(t_stash *s_stash, int linelen)
{
	ssize_t	i;
	char	*line;

	if (!s_stash)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (linelen + 1));
	if (!line)
		return (free(s_stash->stash), s_stash->stash = NULL, NULL);
	i = -1;
	line[linelen] = '\0';
	while (++i < linelen)
		line[i] = s_stash->stash[i];
	return (line);
}

/** char *gnl_delete_first_line(t_stash *s_stash, int linelen)
 * @brief Function to delete the first line on s_stash.stash. It works as
 * memmove. After moving the memory from (i + linelen) to (i), changes the 
 * remainng chars on s_stash.stash to null.
 * Error handling:
 *		when s_stash is null, returns null
 * @param s_stash, poiter to struct to update
 * @param linelen, size of memory to move
 * @return char*, s_stash.stash updated
 */
char	*gnl_delete_first_line(t_stash *s_stash, int linelen)
{
	ssize_t	i;

	if (!s_stash)
		return (NULL);
	i = -1;
	while (s_stash->stash[++i + linelen] != '\0')
		s_stash->stash[i] = s_stash->stash[i + linelen];
	while (s_stash->stash[i] != '\0')
		s_stash->stash[i++] = '\0';
	return (s_stash->stash);
}

/** char *gnl_get_line(t_stash *s_stash)
 * @brief Function that returns the next line on s_stash.stash and updates
 * s_stash.nwline_i and s_stash.slen
 * In orderr to call gnl_save_new_line() and gnl_delete_new_line(), it gets
 * the linelen considering if there's a newline or not (end of file)
 * Error handling:
 *		linelen protected
 *		line returned from save_first_line() protected
 * @param s_stash, pointer to static struct
 * @return char*, line to be returned
 */
char	*gnl_get_line(t_stash *s_stash)
{
	char	*line;
	int		linelen;

	if (!s_stash)
		return (NULL);
	if (s_stash->nwline_i != 0)
		linelen = s_stash->nwline_i;
	else
		linelen = s_stash->stlen;
	if (linelen == 0)
		return (NULL);
	line = gnl_save_first_line(s_stash, linelen);
	if (!line)
		return (NULL);
	s_stash->stash = gnl_delete_first_line(s_stash, linelen);
	return (line);
}
