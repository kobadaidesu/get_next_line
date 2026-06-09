/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakobaya <dakobaya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:59:32 by kobadai           #+#    #+#             */
/*   Updated: 2026/06/09 13:54:26 by dakobaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*find_newline(t_gnl *state)
{
	size_t	i;

	if (state == NULL || state->data == NULL)
		return (NULL);
	i = 0;
	while (i < state->len)
	{
		if (state->data[i] == '\n')
			return (state->data + i);
		i++;
	}
	return (NULL);
}

static int	read_to_state(int fd, t_gnl **state)
{
	ssize_t	bytes;

	if (ft_init_state(state) == GNL_ERROR)
		return (GNL_ERROR);
	bytes = 1;
	while (find_newline(*state) == NULL && bytes > 0)
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
		(*state)->len += (size_t)bytes;
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
	static t_gnl	*state[OPEN_MAX];
	char			*line;
	size_t			len;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_to_state(fd, &state[fd]) == GNL_ERROR)
		return (NULL);
	if (state[fd] == NULL || state[fd]->len == 0)
		return (ft_clear_state(&state[fd]));
	len = ft_line_len(state[fd]);
	line = make_line(state[fd], len);
	if (line == NULL)
		return (ft_clear_state(&state[fd]));
	trim_state(&state[fd], len);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// static void	print_line(int fd)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	if (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// }

// int	main(void)
// {
// 	int	fd1;
// 	int	fd2;

// 	fd1 = open("test.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	if (fd1 < 0 || fd2 < 0)
// 		return (1);
// 	print_line(fd1);
// 	print_line(fd2);
// 	print_line(fd1);
// 	print_line(fd2);
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }
