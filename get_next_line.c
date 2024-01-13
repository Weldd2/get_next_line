/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amura <amura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:27:04 by antoinemura       #+#    #+#             */
/*   Updated: 2024/01/13 17:34:29 by amura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_from_fd(int fd, char *buffer, int *read_bytes, int *buffer_i)
{
	*buffer_i = 0;
	*read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (*read_bytes > 0)
		buffer[*read_bytes] = '\0';
	else if (*read_bytes < 0)
		buffer[0] = '\0';
	return (*read_bytes);
}

char	*append_char_to_line(char *line, int *line_l, char c)
{
	char	*new_line;

	new_line = ft_realloc(line, *line_l, *line_l + 2);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	new_line[*line_l] = c;
	(*line_l)++;
	new_line[*line_l] = '\0';
	return (new_line);
}

char	*handle_line_br(char *line, char *buffer, int *buffer_i, int *line_l)
{
	line = append_char_to_line(line, line_l, buffer[*buffer_i]);
	if (!line)
		return (NULL);
	(*buffer_i)++;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	read_b = 0;
	static int	i = 0;
	char		*line;
	int			line_l;

	line_l = 0;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (i >= read_b && (read_from_fd(fd, buffer, &read_b, &i) <= 0))
		{
			if (read_b < 0)
				return (free(line), NULL);
			return (line);
		}
		if (buffer[i] == '\n' || buffer[i] == '\0')
			return (handle_line_br(line, buffer, &i, &line_l));
		line = append_char_to_line(line, &line_l, buffer[i++]);
		if (!line)
			return (NULL);
	}
}
