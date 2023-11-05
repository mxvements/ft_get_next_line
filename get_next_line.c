/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:00:55 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/05 19:52:15 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*update_stash(char **stash, char **buff)
{

}

char	*read_file(int fd, char *stash)
{
	char	*buff;
	size_t	readbytes;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!stash)
		return (NULL);
	readbytes = read(fd, buff, BUFFER_SIZE);
	if (readbytes > BUFFER_SIZE)//read error
	{
		free(buff);
		return (NULL);
	}
	if (readbytes == 0) //file ending
	{
		return (stash);//placeholder
	}
	buff[readbytes] = '\0';
	stash = update_stash(&stash, &buff);
	return (stash);
}
/*
char	*update_data(char **stash)
{
	char	*line;

	line = save_first_line(*stash);//TODO
	if (!line)
	{
		free(*stash);
		free(stash);
		*stash = NULL;
		return (NULL);
	}
	*stash = delete_saved_line(*stash);//TODO
	if (!(*stash))
		return (NULL);
	return (line);
}
*/
char	*get_next_line(int fd)
{
	static char *stash;
	char		*line;

	//TODO: protect fd, BUFFER_SIZE and read()
	/*if (ft_strchr(stash, '\n'))
		return(update_data(&stash));*/
	stash = read_file(fd, stash); //read_file uses read and BUFFER_SIZE
	if (!stash)
		return (NULL);
	/*if (ft_strchr(stash, '\n'))
		return(update_data(&stash));*/
	return (line);
}

int	main(void)
{
	int	fd;

	fd = open("./file.txt", O_RDONLY);
	get_next_line(fd);
	close(fd);

	return (0);
}
