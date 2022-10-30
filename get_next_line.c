
#include "get_next_line.h"

static void	*ft_free(char *str, char *str2)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	return (NULL);
}

static int	ft_endline(char *src)
{
	int	i;

	i = -1;
	if (!src)
		return (-1);
	while (src[++i])
	{
		if (src[i] == '\n')
			return (i);
	}
	return (-1);
}

static char	*out(char *line, char **rest)
{
	int		i;
	char	*dst;
	int		j;

	i = 1;
	while (line[i - 1] != '\n' && line[i])
		i++;
	j = i;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (ft_free(line, NULL));
	dst[i] = '\0';
	while (--i >= 0)
		dst[i] = line[i];
	if ((int)ft_strlen(line) > j)
	{
		*rest = ft_strdup(line + j);
		if (!*rest)
			return (ft_free(line, dst));
	}
	free(line);
	return (dst);
}

static int	ft_rest_manager(char **line, char **rest)
{
	*line = ft_strdup(*rest);
	free(*rest);
	*rest = NULL;
	if (!(*line))
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			ret;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, buffer, 0))
		return (NULL);
	line = NULL;
	ret = BUFFER_SIZE;
	while (ft_endline(line) == -1 && ret == BUFFER_SIZE)
	{
		if (rest)
			if (ft_rest_manager(&line, &rest) == 0)
				return (NULL);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		if (ft_endline(line) == -1)
			ret = read(fd, buffer, BUFFER_SIZE);
		if ((ret > 0))
			line = ft_strjoin(line, (char *)buffer);
		else if (ret == 0 && !line)
			return (NULL);
		if (!line)
			return (NULL);
	}
	return (out(line, &rest));
}
