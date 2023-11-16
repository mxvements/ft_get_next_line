/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:48:44 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/13 18:48:46 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line_bonus.h"
#include <fcntl.h>

int	main(void)
{
	int		fd[4];
	int		i;
	char	*gnl;

	fd[0] = open("./files/file1.txt", O_RDONLY);
	fd[1] = open("./files/one_line_no_newline.txt", O_RDONLY);
	fd[2] = open("./files/only_newlines.txt", O_RDONLY);
	fd[3] = open("./files/42_nl.txt", O_RDONLY);
	while (1)
	{
		i = 0;
		while (i < 4)
		{
			gnl = get_next_line(fd[i]);
			if (gnl == NULL)
				break ;
			printf("%i -> %s\n", i, gnl);
			free(gnl);
			i++;
		}
	}
	i = 0;
	while (fd[i] != -1)
	{
		close(fd[i]);
		i++;
	}
	//system("leaks -q a.out");
	return (0);
}
