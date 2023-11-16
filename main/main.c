/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:40:18 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/13 17:40:20 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("./files/file1.txt", O_RDONLY);
	//fd = open("./files/one_line_no_newline.txt", O_RDONLY);
	//fd = open("./files/only_newlines.txt", O_RDONLY);
	//fd = open("./files/42_nl.txt", O_RDONLY);
	//fd = 0;
	//fd = -1;
	//fd = 50;
	while (1)
	{
		gnl = get_next_line(fd);
		if (gnl == NULL)
			break ;
		printf("%s", gnl);
		free(gnl);
	}
	close(fd);
	//system("leaks -q a.out");
	return (0);
}
