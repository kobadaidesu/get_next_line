/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kobadai <kobadai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 16:32:40 by kobadai           #+#    #+#             */
/*   Updated: 2026/05/03 17:12:11 by kobadai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_getchar(void)
{
	static char	buf[BUFFER_SIZE];
	static char	*bufp;
	static int	n = 0;

	if (n == 0)
	{
		n = read(0, buf, BUFFER_SIZE);
		bufp = buf;
	}
	--n;
	if (n >= 0)
		return ((unsigned char)*bufp++);
	return (EOF);
}
