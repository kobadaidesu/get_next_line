/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kobadai <kobadai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 16:32:40 by kobadai           #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by kobadai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_memcpy_gnl(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_clear_state(t_gnl **state)
{
	if (state == NULL || *state == NULL)
		return (NULL);
	free((*state)->data);
	free(*state);
	*state = NULL;
	return (NULL);
}

int	ft_init_state(t_gnl **state)
{
	if (*state != NULL)
		return (GNL_OK);
	*state = malloc(sizeof(t_gnl));
	if (*state == NULL)
		return (GNL_ERROR);
	(*state)->data = NULL;
	(*state)->len = 0;
	(*state)->cap = 0;
	return (GNL_OK);
}

int	ft_ensure_capacity(t_gnl *state, size_t need)
{
	char	*new_data;
	size_t	new_cap;

	if (need + 1 <= state->cap)
		return (GNL_OK);
	new_cap = state->cap;
	if (new_cap == 0)
		new_cap = GNL_BUFFER_SIZE + 1;
	while (new_cap <= need)
		new_cap *= 2;
	new_data = malloc(new_cap);
	if (new_data == NULL)
		return (GNL_ERROR);
	ft_memcpy_gnl(new_data, state->data, state->len);
	new_data[state->len] = '\0';
	free(state->data);
	state->data = new_data;
	state->cap = new_cap;
	return (GNL_OK);
}

size_t	ft_line_len(t_gnl *state)
{
	size_t	i;

	if (state == NULL || state->data == NULL)
		return (0);
	i = 0;
	while (i < state->len)
	{
		if (state->data[i] == '\n')
			return (i + 1);
		i++;
	}
	return (state->len);
}
