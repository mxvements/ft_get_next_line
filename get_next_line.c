/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:00:55 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/06 17:23:48 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*read_file(int fd, char *stash)
{
	size_t	readbytes;

	stash = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!stash)
		return (NULL);
	readbytes = read(fd, stash, BUFFER_SIZE);
	if (readbytes > BUFFER_SIZE)//read error
	{
		free(stash);
		return (NULL);
	}
	if (readbytes == 0) //file ending
	{
		return (stash);//placeholder
	}
	stash[readbytes] = '\0';
	printf("BYTES_READ:\n%zu\n", readbytes);
	printf("BUFFER_READ:\n%s\n", stash);
	return (stash);
}
char	*save_first_line(char *stash)
{
	char	*line;
	size_t	i;

	i = 0;
	while (stash[i] != '\0')
	{
		if (stash[i] == '\n')
			break;
		i++;
	}
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (--i > 0)
		line[i] = stash[i];
	line[0] = stash[0];
	return (line);	
}

char	*update_data(char **stash)
{
	char	*line;

	line = save_first_line(*stash);//TODO
	if (!line)
	{
		free(*stash);
		stash = NULL;
		return (NULL);
	}
	printf("LINE SAVED:\n%s\n", line);
	printf("STASH WHEN LINE SAVED:\n%s\n", *stash);
	/**stash = delete_saved_line(*stash);//TODO
	if (!(*stash))
		return (NULL);*/
	return (line);
}

int	ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i++] == c)
			return (1);
	}
	return (0);
}

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
	if (ft_strchr(stash, '\n'))
		return(update_data(&stash));
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
