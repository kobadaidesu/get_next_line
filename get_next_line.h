/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kobadai <kobadai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 16:29:24 by kobadai           #+#    #+#             */
/*   Updated: 2026/05/05 16:29:49 by kobadai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define GNL_BUFFER_SIZE BUFFER_SIZE
# define GNL_ERROR 0
# define GNL_OK 1

typedef struct s_gnl
{
	char	*data;
	size_t	len;
	size_t	cap;
}	t_gnl;

void	ft_memcpy_gnl(char *dst, const char *src, size_t n);
char	*ft_clear_state(t_gnl **state);
int		ft_init_state(t_gnl **state);
int		ft_ensure_capacity(t_gnl *state, size_t need);
size_t	ft_line_len(t_gnl *state);
char	*get_next_line(int fd);

#endif
