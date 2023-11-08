/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:00:55 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/08 01:17:04 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*gnl_update_stash(char **stash, char **buff)
{
	//ESTO ME HACE SEGFAULT OBVIOOOO
	size_t	i;
	size_t	j;

	i = 0;
	if (!(*stash))
		return (*buff);
	while (*stash[i] != '\0')
		i++;
	while (*buff[j] != '\0')
		*stash[i + j] = *buff[j++];
	*stash[i + j] = '\0';
	return (*stash);
}

char	*gnl_read_file(int fd, char **stash)
{
	char	*buff;
	size_t	readbytes;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readbytes = read(fd, buff, BUFFER_SIZE);
	if (readbytes > BUFFER_SIZE)//read error
	{
		free(buff);
		return (NULL);
	}
	*stash = gnl_update_stash(stash, &buff);
	if (readbytes == 0) //file ending
	{
		return (*stash);//placeholder
	}
	stash[readbytes] = '\0';
	printf("BYTES_READ:\n%zu\n", readbytes);
	printf("BUFFER_READ:\n%s\n", *stash);
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char *stash;
	char		*line;
	int			endline_i;

	//TODO: protect fd, BUFFER_SIZE and read()
	
	/*if (ft_strchr(stash, '\n'))
		return(update_data(&stash));*/
	stash = gnl_read_file(fd, &stash); //read_file uses read and BUFFER_SIZE
	if (!stash)
		return (NULL);
	endline_i = gnl_strchr(stash, '\n');
	if (endline_i != 0)
		return(gnl_update_line(&stash, &endline_i)); //TODO: quitar el return
	return (line);
}

int	main(void)
{
	int	fd;

	fd = open("./file.txt", O_RDONLY);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	close(fd);

	return (0);
}
