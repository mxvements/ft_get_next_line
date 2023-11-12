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

//2
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

//3
char	*gnl_read_file(int fd, t_stash *s_stash)
{
	char	*buff;
	char	*temp;

	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	s_stash->readbytes = read(fd, buff, BUFFER_SIZE);
	buff[s_stash->readbytes] = '\0'; //heap-buffer-overflow
	if (s_stash->readbytes <= 0)
	{
		//update STRUCT to know there was an error/i got to the end of file
		return (free(buff), NULL);
	}
	if (!(		s_stash->stash))
	{
		temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(temp))
			return (free(buff), NULL);
		temp = gnl_memcpy(&temp, &buff, s_stash->readbytes);
		return (free(buff), temp);
	}
	temp = gnl_strjoin(&s_stash->stash, &buff);
	free(s_stash->stash);
	return (free(buff), temp);
}
//4
void	gnl_update_struct(int fd, t_stash *s_stash)
{
	s_stash->stash = gnl_read_file(fd, s_stash);
	if (!s_stash->stash)
		return ;
	s_stash->nwline_i = gnl_strchr(s_stash->stash, '\n');
	s_stash->stlen = gnl_strlen(s_stash->stash);
	return ;
}
//5
char	*get_next_line(int fd)
{	
	static t_stash	s_stash;

	if (fd < 0 || fd > 256 || BUFFER_SIZE < 1)
		return (NULL); //probably, free s_stash.stash
	if (s_stash.stash) //if stash is not empty
	{
		//TO BE UPDATED WITH THE STRUCT
		//s_stash.nwline_i = gnl_strchr(s_stash.stash, '\n'); //and has a newlines //UPDATE STRUCT
		//s_stash.stlen = gnl_strlen(s_stash.stash);//this should already be updated
		return (gnl_get_line(&s_stash));
	}
	while (!s_stash.stash)
	{
		gnl_update_struct(fd, &s_stash);
	}
	return (gnl_get_line(&s_stash));
}

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("./files/file1.txt", O_RDONLY);

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
