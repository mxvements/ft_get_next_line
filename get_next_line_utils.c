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

//1
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

//2
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

//3
char	*gnl_save_first_line(t_stash *s_stash, int linelen)
{
	ssize_t	i;
	char	*line;

	if (!s_stash)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (linelen + 1));
	if (!line)
		return (NULL);
	i = -1;
	line[linelen] = '\0';
	while (++i < linelen)
		line[i] = s_stash->stash[i];
	return (line);
}

//4
char	*gnl_delete_first_line(t_stash *s_stash, int linelen)
{
	ssize_t	i;

	if (!s_stash)
		return (NULL);
	//mem move
	i = -1;
	while (s_stash->stash[++i + linelen] != '\0')
		s_stash->stash[i] = s_stash->stash[i + linelen];
	while (s_stash->stash[i] != '\0')
		s_stash->stash[i++] = '\0';
	//update struct
	s_stash->stlen = gnl_strlen(s_stash->stash);
	s_stash->nwline_i = gnl_strchr(s_stash->stash, '\n');
	return (s_stash->stash);
}

//5
char	*gnl_get_line(t_stash *s_stash)
{
	char	*line;
	int		linelen;

	if (!s_stash)
		return (NULL);
	if (s_stash->readbytes != 0) //include the option that maybe there is no newline
		linelen = s_stash->nwline_i;
	else
		linelen = s_stash->stlen;
	if (linelen == 0)
		return (NULL);
	line = gnl_save_first_line(s_stash, linelen);
	if (!line)
		return (NULL);
	s_stash->stash = gnl_delete_first_line(s_stash, linelen);
	if (!(s_stash->stash))
		return (free(line), NULL);
	return (line);
}

/* PRUBEAS CON STATIC*/
/*
int	funct(void)
{
	static int	i = 0;

	return (i++);
}

void	main(void)
{
	printf("%d\n", funct());
	printf("%d\n", funct());
	printf("%d\n", funct());
}*/
