/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:19:21 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/08 20:34:56 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	gnl_strchr(char *stash, char c)
{
	size_t	i;

	i = 0;
	while (stash[i] != '\0')
	{
		if (stash[i] == c)
			return (++i);
		i++;
	}
	return (0);
}

void	gnl_save_first_line(char **line, char *stash, int *endline_i)
{
	size_t	i;

	i = (size_t)*endline_i;
	line[0][i] = '\0';
	while (--i > 0)
		line[0][i] = stash[i];
	line[0][0] = stash[0];
	return ;	
}

char	*gnl_delete_first_line(char *stash, int *endline_i)
{
	size_t	i;

	i = 0;
	while (stash[i + *endline_i] != '\0')
	{
		stash[i] = stash[i + *endline_i];
		i++;
	}
	while (stash[i] != '\0')
		stash[i++] = '\0';
	printf("STASH UPDATED:\n%s\n", stash);
	return (stash);
}

char	*gnl_update_line(char **stash, int *endline_i)
{
	char	*line;

	line = (char *)malloc(sizeof(char) * (*endline_i + 1)); //FREE THIS
	if (!line)
		return (NULL);
	gnl_save_first_line(&line, *stash, endline_i);
	
	printf("LINE SAVED:\n%s\n", line);
	*stash = gnl_delete_first_line(*stash, endline_i);
	if (!(*stash))
		return (NULL);
	return ((char *)line);
}
//TODO gnl_free()


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
