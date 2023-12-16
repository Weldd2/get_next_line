
#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *src, char *dest)
{
	int	i;

	i = 0;
	while(src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_strcat(char *src, char *dest)
{
	int	i;
	int	dest_l;

	i = 0;
	dest_l = ft_strlen(dest);
	while (src[i])
	{
		dest[i + dest_l] = src[i]; 
		i++;
	}
	return (dest);
}

char	*ft_calloc(char *line)
{
	char	*save;

	save = malloc(ft_strlen(line));
	ft_strcpy(line, save);
	free(line);
	line = malloc(ft_strlen(save) + 1);
	ft_strcpy(save, line);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffer;
	int		bytes_read;

	line = malloc(1);
	buffer = malloc(1);
	while (1)
	{
		line = ft_calloc(line);
		bytes_read = read(fd, buffer, 1);
		ft_strcat(buffer, line);
		if (bytes_read == 0 && ft_strlen(line) == 0)
			return (NULL) ;
		if (line[ft_strlen(line) - 1] == '\n' || bytes_read == 0)
			break ;
	}
	return (line);
}

int main(void) {

	FILE *file = fopen("get_next_line.c", "r");
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}

	int fd = fileno(file);
	char *line;

	while ((line = get_next_line(fd)) != NULL) {
		printf("a%s", line);
		free(line);
	}

	fclose(file);
	return 0;
}
