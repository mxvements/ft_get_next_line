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
	while ((*stash)[++i] != '\0')
		temp[i] = (*stash)[i];
	while (buff[0][++j] != '\0')
		temp[i + j] = (*buff)[j];
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
		return (free(s_stash->stash), NULL);
	s_stash->readbytes = read(fd, buff, BUFFER_SIZE);
	if (s_stash->readbytes < 0)
		return (free(buff), free(s_stash->stash), buff = NULL, NULL);
	if (s_stash->readbytes == 0 || *buff == '\0')
		return (free(buff), buff = NULL, s_stash->stash);
	buff[s_stash->readbytes] = '\0';
	if (!(s_stash->stash))
	{
		temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(temp))
			return (free(buff), buff = NULL, NULL);
		temp = gnl_memcpy(&temp, &buff, s_stash->readbytes);
		return (free(buff), buff = NULL, temp);
	}
	temp = gnl_strjoin(&s_stash->stash, &buff);
	free(s_stash->stash);
	return (free(buff), buff = NULL, temp);
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
	char			*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	while (s_stash.nwline_i == 0)
	{
		gnl_update_struct(fd, &s_stash);
		if (!s_stash.stash)
			return (NULL);
		if (s_stash.readbytes < BUFFER_SIZE) //reached endfile
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
