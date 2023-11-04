/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:00:55 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/03 17:07:02 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h";

char	*update_data(char **stash)
{
	char	*line;

	line = save_first_line(*stash);
	if (!line)
	{
		free(*stash);
		free(stash);
		*stash = NULL;
		return (NULL);
	}
	*stash = delete_saved_line(*stash);
	if (!(*stash))
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char *stash;
	char		*line;

	//TODO: protect fd, BUFFER_SIZE and read()
	if (ft_strchr(stash, '\n'))
		return(update_data(&stash));
	stash = read_file(fd, stash); //read_file uses read and BUFFER_SIZE
	if (!stash)
		return (NULL);
	if (ft_strchr(stash, '\n'))
		return(update_data(&stash));
	return (line);
}

int	main(void)
{
	return (0);
}
