
#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *line, char *buffer)
{
	char	*s;
	int		i;

	s = (char *)malloc(sizeof(char) * (ft_strlen(buffer) + ft_strlen(line) + 1));
	if (!s)
		return (NULL);
	i = -1;
	while (line[++i])
		s[i] = line[i];
	while (*buffer && *buffer != '\n')
	{
		s[i] = *buffer;
		i++;
		buffer++;
	}
	if (*buffer == '\n')
	{
		s[i] = '\n';
		buffer++;
		i++;
	}
	s[i] = '\0';
	free(line);
	return (s);
}

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


char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer = NULL;
	int			bytes_read;

	if (buffer == NULL)
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = -1;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		if (bytes_read == 0 && ft_strlen(buffer) == 0)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		line = ft_strjoin(line, buffer);
		if (*buffer == '\n' || *(buffer + 1) == '\0')
			break ;
	}
	return (line);
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
		printf("%s", line);
		free(line);
	}

	fclose(file);
	return 0;
}
