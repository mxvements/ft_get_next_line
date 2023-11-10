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
/*
void	gnl_memcpy(char **dst, char **src)
{
	size_t	i;
	
	i = 0;
	while (src[0][i] != '\0')
	{
		dst[0][i] = src[0][i];
		i++;
	}
	dst[0][i] = '\0';
	return ;
	
}*/

//3
char	*gnl_update_stash(char **stash, char **buff)
{
	int	i;
	int	j;
	size_t	len;
	char	*temp;

	i = -1;
	j = -1;
	if (!(*stash))
		return (*buff); //*stash = *buff copy strings
	else
	{
		len = gnl_strlen(*stash);
		temp = (char *)malloc(sizeof(char) + (BUFFER_SIZE + len + 1));
		if (!(temp))
			return (NULL);
		//concatenate strings (stash and buff) on temp
		while (stash[0][++i] != '\0')
			temp[i] = stash[0][i];
		while (buff[0][++j] != '\0')
			temp[i + j] = buff[0][j];
		temp[i + j] = '\0';
		return (temp); //copy strings
		//FREE TEMP
	}
}

//4
char	*gnl_read_file(int fd, char **stash)
{
	char	*buff;
	size_t	readbytes;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readbytes = read(fd, buff, BUFFER_SIZE);
	if (readbytes > BUFFER_SIZE)//read error
		return (free(buff), buff = NULL, NULL);
	if (readbytes == 0) //file ending
	{
		free(buff);
		return (*stash);//placeholder
	}
	buff[readbytes] = '\0';
	*stash = gnl_update_stash(stash, &buff);
	//printf("BYTES_READ:\n%zu\n", readbytes);
	//printf("BUFFER_READ:\n%s\n", *stash);
	return (*stash); //CANT FREE BUFF WHILE MEMORY ISNT COPIED
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
