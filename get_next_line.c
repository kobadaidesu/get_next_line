/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kobadai <kobadai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 16:29:32 by kobadai           #+#    #+#             */
/*   Updated: 2026/05/05 16:33:24 by kobadai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*end_read(char *line, int is_error)
{
	if (is_error || !line[0])
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	temp[2];
	char	*line;
	char	*new_line;
	int		c;

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	temp[1] = '\0';
	c = ft_getc(fd);
	while (c != EOF && c != -2)
	{
		temp[0] = c;
		new_line = ft_strjoin(line, temp);
		free(line);
		if (!new_line)
			return (NULL);
		line = new_line;
		if (temp[0] == '\n')
			return (line);
		c = ft_getc(fd);
	}
	return (end_read(line, c == -2));
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
