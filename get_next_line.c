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

//1
void	gnl_free(char **s)
{
	size_t i;

	i = 0;
	while (s[i] != NULL)
		free(s[i]);
	free(s);
	return ;
}

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
char	*gnl_update_stash(char **stash, char **buff)
{
	int		i;
	int		j;
	size_t	len;
	char	*temp;

	i = -1;
	j = -1;
	/*len = gnl_strlen(*stash);
	temp = (char *)malloc(sizeof(char) + (BUFFER_SIZE + len + 1));
	if (!(temp))
		return (NULL);*/
	//concatenate strings (stash and buff) on temp
	while (stash[0][++i] != '\0')
		temp[i] = stash[0][i];
	while (buff[0][++j] != '\0')
		temp[i + j] = buff[0][j];
	temp[i + j] = '\0';
	return (gnl_memcpy(stash, &temp, (BUFFER_SIZE + len))); //copy strings
	//FREE TEMP
}

//4
char	*gnl_read_file(int fd, char **stash)
{
	char	*buff;
	char	*temp;
	size_t	readbytes;
	size_t	len;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readbytes = read(fd, buff, BUFFER_SIZE);
	buff[readbytes] = '\0';
	if (readbytes > BUFFER_SIZE)//read error
		return (free(buff), buff = NULL, NULL);
	if (readbytes == 0) //file ending
		return (free(buff), buff = NULL, *stash);
	if (!(*stash))
	{
		temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*temp))
			return (NULL);
		return(gnl_memcpy(&temp, &buff, BUFFER_SIZE)); //copy buff on temp
	}
	else
	{
		len = gnl_strlen(*stash);
		temp = (char *)malloc(sizeof(char) + (BUFFER_SIZE + len + 1));
		if (!(temp))
			return (NULL);
		*stash = gnl_update_stash(stash, &buff);
	}
	//printf("BYTES_READ:\n%zu\n", readbytes);
	//printf("BUFFER_READ:\n%s\n", *stash);
	return (free(buff), buff = NULL, *stash); //CANT FREE BUFF WHILE MEMORY ISNT COPIED
}

//5
char	*get_next_line(int fd)
{	
	static char *stash;
	char		*line;
	int			endline_i;

	//TODO: protect fd, BUFFER_SIZE and read()
	
	/*if (ft_strchr(stash, '\n'))
		return(update_data(&stash));*/
	endline_i = 0;
	line = NULL;
	while (endline_i == 0)
	{
		stash = gnl_read_file(fd, &stash);
		endline_i = gnl_strchr(stash, '\n');
	}
	if (endline_i != 0)
		line = gnl_update_line(&stash, &endline_i);
	return (line);
}

int	main(void) 
{
	int	fd;
	char	*gnl;

	fd = open("./file.txt", O_RDONLY);
	gnl = get_next_line(fd);
	printf("MAIN:\n%s", gnl);
	free(gnl);
	gnl = get_next_line(fd);
	printf("MAIN:\n%s", gnl);
	free(gnl);
	close(fd);

	return (0);
}
