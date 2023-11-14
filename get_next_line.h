/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:01:06 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/09 22:47:01 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct stash
{
	int		stlen;
	int		nwline_i;
	ssize_t	readbytes;
	char	*stash;
}	t_stash;

char	*gnl_memcpy(char **dst, char **src, size_t len);
char	*gnl_strjoin(char **stash, char **buff);
char	*gnl_read_file(int fd, t_stash *s_stash);
void	gnl_update_struct(int fd, t_stash *s_stash);
char	*get_next_line(int fd);
int		gnl_strlen(char *s);
int		gnl_strchr(char *stash, char c);
char	*gnl_save_first_line(t_stash *s_stash, int linelen);
char	*gnl_delete_first_line(t_stash *s_stash, int linelen);
char	*gnl_get_line(t_stash *s_stash);

#endif
