/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:01:06 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/08 20:04:07 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 64
#endif

int		gnl_strlen(char *s);
int		gnl_strchr(char *stash, char c);
char	*gnl_read_file(int fd, char **stash);
//char	*gnl_save_first_line(char *stash, int *endline_i);
char	*gnl_update_line(char **stash, int *endline_i);
char	*get_next_line(int fd);

#endif
