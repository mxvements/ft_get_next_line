/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:19:21 by luciama2          #+#    #+#             */
/*   Updated: 2023/11/04 16:19:23 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(char *stash, char c)
{
	size_t	i;

	i = 0;
	while (stash[i] != '\0')
	{
		if (stash[i] == c)
			return (1);
	}
	return (0);
}