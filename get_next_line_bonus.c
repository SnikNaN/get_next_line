#include "get_next_line_bonus.h"

static int	ft_prcs_rest(char **rest, char **new_line)
{
	size_t	i;
	char	*new_rest;

	if (!new_line || !(*rest))
		return (-1);
	i = 0;
	while (*rest && (*rest)[i])
	{
		if ((*rest)[i] == '\n')
		{
			*new_line = ft_substr(*rest, 0, i);
			if (!(*new_line))
				return (-1);
			new_rest = ft_substr(*rest, i + 1, ft_strlen(*rest) - i);
			if (!new_rest)
				return (-1);
			free(*rest);
			*rest = new_rest;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_free(char **s1, char **s2, int ret_value)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (ret_value);
}

int	get_next_line(int fd, char **line)
{
	static char	*rest[1024];
	char		*buf;
	ssize_t		cnt;

	if ((read(fd, 0, 0) < 0) || !line || (BUFFER_SIZE <= 0))
		return (-1);
	cnt = 1;
	while (cnt > 0)
	{
		if (rest[fd])
			cnt = ft_prcs_rest(&(rest[fd]), line);
		if (cnt == -1)
			return (ft_free(&(rest[fd]), &buf, -1));
		if (rest[fd] && cnt)
			return (1);
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (ft_free(&(rest[fd]), NULL, -1));
		cnt = read(fd, buf, BUFFER_SIZE);
		rest[fd] = ft_strjoin(&(rest[fd]), &buf);
		if (!(rest[fd]) || cnt < 0)
			return (ft_free(&(rest[fd]), &buf, -1));
	}
	*line = ft_strdup(rest[fd]);
	return (ft_free(&(rest[fd]), &buf, ft_prcs_rest(line, line)));
}
