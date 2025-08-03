/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:31:26 by hshehab           #+#    #+#             */
/*   Updated: 2024/07/23 19:15:39 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	new_buffer_size = 0;
	static int	position = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (read_from_file(fd, buffer, &new_buffer_size, &position));
}
