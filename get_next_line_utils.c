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
char	*gnl_save_first_line(char *stash, int *linelen)
{
	ssize_t	i;
	char	*line;

	if (!stash || !linelen)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (*linelen + 1));
	if (!line)
		return (NULL);
	i = -1;
	line[*linelen] = '\0';
	while (++i < *linelen)
		line[i] = stash[i];
	return (line);
}

//4
char	*gnl_delete_first_line(char *stash, int *linelen)
{
	size_t	i;

	//potencialmente, actualizar la longitud del stash
	i = 0;
	if (!stash || !linelen)
		return (NULL);
	while (stash[i + *linelen] != '\0')
	{
		stash[i] = stash[i + *linelen];
		i++;
	}
	while (stash[i] != '\0')
		stash[i++] = '\0';
	return (stash);
}

//5
char	*gnl_get_line(char **stash, int *endline_i)
{
	char	*line;

	if (!stash || !endline_i)
		return (NULL);
	line = gnl_save_first_line(*stash, endline_i);
	if (!line)
		return (NULL);
	*stash = gnl_delete_first_line(*stash, endline_i);
	if (!(*stash))
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
