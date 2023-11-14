/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:24:08 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/13 18:40:29 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static t_stash	s_stash[OPEN_MAX];
	char			*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	while (s_stash[fd].nwline_i == 0)
	{
		gnl_update_struct(fd, &s_stash[fd]);
		if (!s_stash[fd].stash)
			return (NULL);
		if (s_stash[fd].readbytes < BUFFER_SIZE)
			break ;
	}
	line = gnl_get_line(&s_stash[fd]);
	s_stash[fd].nwline_i = gnl_strchr(s_stash[fd].stash, '\n');
	s_stash[fd].stlen = gnl_strlen(s_stash[fd].stash);
	if (s_stash[fd].stlen == 0)
	{
		free(s_stash[fd].stash);
		s_stash[fd].stash = NULL;
	}
	return (line);
}
