#include "get_next_line_bonus.h"

static char	*end_read(char *line, int is_error)
{
	if (!line || is_error || !line[0])
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	ft_getc_fd(int fd, t_gnl *state)
{
	if (state->n == 0)
	{
		state->n = read(fd, state->buf, BUFFER_SIZE);
		if (state->n == 0)
			return (EOF);
		if (state->n < 0)
		{
			state->n = 0;
			return (-2);
		}
		state->bufp = state->buf;
	}
	state->n--;
	return ((unsigned char)*state->bufp++);
}

char	*get_next_line(int fd)
{
	static t_gnl	state[OPEN_MAX];
	char			temp[2];
	char			*line;
	char			*new_line;
	int				c;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	line = malloc(1);
	line[0] = '\0';
	temp[1] = '\0';
	c = ft_getc_fd(fd, &state[fd]);
	while (c != EOF && c != -2)
	{
		temp[0] = c;
		new_line = ft_strjoin(line, temp);
		free(line);
		line = new_line;
		if (temp[0] == '\n')
			return (line);
		c = ft_getc_fd(fd, &state[fd]);
	}
	return (end_read(line, c == -2));
}
