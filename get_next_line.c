/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:57:17 by antoinemura       #+#    #+#             */
/*   Updated: 2023/12/16 15:05:04 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	static int	buffer_size = 0;
	char		*line;
	int			i;
	int			line_size;

	if (buffer_size == 0)
	{
		buffer = malloc(BUFFER_SIZE);
		buffer_size = read(fd, buffer, BUFFER_SIZE);
	}
	else
		if (buffer[0] == '\0')
			return (NULL);
	line_size = 0;
	while (line_size < buffer_size && buffer[line_size - 1] != '\n' 
											&& buffer[line_size] != '\0')
		line_size++;
	line = malloc(line_size + 2);
	for (i = 0; i < line_size; i++)
		line[i] = buffer[i];
	line[i + 1] = '\0';
	buffer += (line_size + 1);
	buffer_size -= (line_size + 1);
	return (line);
}
