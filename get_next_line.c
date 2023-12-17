
#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		n--;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

int	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

char	*ft_strjoin(char *line, char *buffer, int j)
{
	char	*s;
	int		i;

	s = (char *)malloc(sizeof(char) * (ft_strlen(buffer) + ft_strlen(line) + 1));
	if (!s)
		return (NULL);
	i = -1;
	while (line[++i])
		s[i] = line[i];
	while (buffer[j] && buffer[j] != '\n')
	{
		s[i] = buffer[j];
		i++;
		j++;
	}
	if (buffer[j] == '\n')
	{
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	free(line);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	static int	i = 0;
	char		*line;
	int	bytes_read;

	if (buffer == NULL)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
	}
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	bytes_read = 0;
	while (1)
	{
		if (buffer[i] == '\0')
		{
			i = 0;
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read == -1)
			{
				free(buffer);
				free(line);
				return (NULL);
			}
			buffer[bytes_read] = '\0';
		}
		if (bytes_read == 0 && *line != '\0')
			return (line);
		line = ft_strjoin(line, buffer, i);
		while (buffer[i] != '\n' && buffer[i] != '\0')
			i++;
		if (buffer[i] == '\n')
			i++;
		if (bytes_read > 0 && line[i - 1] == '\n')
			return (line);
		if (bytes_read == 0 && *line == '\0')
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		if (bytes_read == 0 && *line != '\0')
			return (line);
	}
}

int main(void) {

	FILE *file = fopen("test", "r");
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}

	int fd = fileno(file);
	char *line;

	while ((line = get_next_line(fd)) != NULL) {
		printf("[%s]", line);
		free(line);
	}

	fclose(file);
	return 0;
}
