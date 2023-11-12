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
#include <fcntl.h>

//2
char	*gnl_memcpy(char **dst, char **src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[0][i] = src[0][i];
		i++;
	}
	dst[0][i] = '\0';
	return (*dst);
}

//3
char	*gnl_strjoin(char **stash, char **buff)
{
	int		i;
	int		j;
	size_t	len;
	char	*temp;

	i = -1;
	j = -1;
	len = gnl_strlen(*stash);
	temp = (char *)malloc(sizeof(char) + (BUFFER_SIZE + len + 1));
	if (!(temp))
		return (NULL);
	while (stash[0][++i] != '\0')
		temp[i] = stash[0][i];
	while (buff[0][++j] != '\0')
		temp[i + j] = buff[0][j];
	temp[i + j] = '\0';
	return (temp);
}

//4
char	*gnl_read_file(int fd, char **stash)
{
	char	*buff;
	char	*temp;
	ssize_t	readbytes;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readbytes = read(fd, buff, BUFFER_SIZE);
	buff[readbytes] = '\0'; //heap-buffer-overflow
	if (readbytes <= 0)
		return (free(buff), NULL);
	if (!(*stash))
	{
		temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(temp))
			return (free(buff), NULL);
		temp = gnl_memcpy(&temp, &buff, readbytes);
		return (free(buff), temp);
	}
	temp = gnl_strjoin(stash, &buff);
	free(*stash);
	stash = NULL;
	return (free(buff), temp);
}

//5
char	*get_next_line(int fd)
{	
	static char	*stash;
	int			endline_i;
	int			stashlen;

	if (fd < 0 || fd > 256 || BUFFER_SIZE < 1)
		return (free(stash), NULL);
	if (stash) //if stash is not empty
	{
		endline_i = gnl_strchr(stash, '\n'); //and has a newlines
		stashlen = gnl_strlen(stash);
		if (endline_i == 0 && stashlen == 0)
			return (free(stash), NULL);
		if (endline_i == 0 && stashlen != 0)
			return(gnl_get_line(&stash, &stashlen));
		return (gnl_get_line(&stash, &endline_i));
	}
	endline_i = 0;
	stashlen = 0;
	while (stashlen == 0)
	{
		stash = gnl_read_file(fd, &stash);
		if (!stash)
			return (free(stash), NULL);
		stashlen = gnl_strlen(stash);
		endline_i = gnl_strchr(stash, '\n');
	}
	if (endline_i == 0 && stashlen != 0)
			return(gnl_get_line(&stash, &stashlen));
	return (gnl_get_line(&stash, &endline_i));
}

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("./files/one_line_no_newline.txt", O_RDONLY);

	while (1)
	{
		gnl = get_next_line(fd);
		printf("%s", gnl);
		if (gnl == NULL)
			break;
		free(gnl);
	}

	close(fd);
	system("leaks -q a.out");
	return (0);
}
