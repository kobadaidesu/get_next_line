/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakobaya <dakobaya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 16:29:32 by kobadai           #+#    #+#             */
/*   Updated: 2026/06/09 13:46:40 by dakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	has_newline(t_gnl *state)
{
	if (state == NULL || state->len == 0)
		return (0);
	return (state->data[ft_line_len(state) - 1] == '\n');
}

static int	read_to_state(int fd, t_gnl **state)
{
	ssize_t	bytes;

	if (ft_init_state(state) == GNL_ERROR)
		return (GNL_ERROR);
	bytes = 1;
	while (!has_newline(*state) && bytes > 0)
	{
		if (ft_ensure_capacity(*state, (*state)->len
				+ GNL_BUFFER_SIZE) == GNL_ERROR)
		{
			ft_clear_state(state);
			return (GNL_ERROR);
		}
		bytes = read(fd, (*state)->data + (*state)->len, GNL_BUFFER_SIZE);
		if (bytes < 0)
		{
			ft_clear_state(state);
			return (GNL_ERROR);
		}
		(*state)->len += bytes;
		(*state)->data[(*state)->len] = '\0';
	}
	return (GNL_OK);
}

static char	*make_line(t_gnl *state, size_t len)
{
	char	*line;

	if (state == NULL || state->len == 0)
		return (NULL);
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	ft_memcpy_gnl(line, state->data, len);
	line[len] = '\0';
	return (line);
}

static void	trim_state(t_gnl **state, size_t len)
{
	size_t	rest;

	if (*state == NULL)
		return ;
	rest = (*state)->len - len;
	if (rest == 0)
	{
		ft_clear_state(state);
		return ;
	}
	ft_memcpy_gnl((*state)->data, (*state)->data + len, rest);
	(*state)->len = rest;
	(*state)->data[rest] = '\0';
}

char	*get_next_line(int fd)
{
	static t_gnl	*state;
	char			*line;
	size_t			len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_to_state(fd, &state) == GNL_ERROR)
		return (NULL);
	if (state == NULL || state->len == 0)
		return (ft_clear_state(&state));
	len = ft_line_len(state);
	line = make_line(state, len);
	if (line == NULL)
		return (ft_clear_state(&state));
	trim_state(&state, len);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
