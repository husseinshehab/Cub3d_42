/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:31:31 by hshehab           #+#    #+#             */
/*   Updated: 2024/07/23 19:16:33 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	read_from_file_new(int fd, char *buffer, int *new_size, int*pos)
{
	*new_size = read(fd, buffer, BUFFER_SIZE);
	*pos = 0;
	return (*new_size);
}

char	*add_character(char c, char *res, int res_len)
{
	char	*new_res;
	int		i;

	i = 0;
	new_res = (char *)malloc(sizeof(char) * (res_len + 2));
	if (!new_res)
		return (NULL);
	while (i < res_len)
	{
		new_res[i] = res[i];
		i++;
	}
	new_res[res_len++] = c;
	new_res[res_len] = '\0';
	return (free(res), new_res);
}

char	*read_from_file(int fd, char *buffer, int *size, int *pos)
{
	char	*res;
	char	c;
	int		res_len;

	res = NULL;
	res_len = 0;
	while (1)
	{
		if (*pos == *size)
		{
			if (read_from_file_new(fd, buffer, size, pos) <= 0)
			{
				if (res_len > 0)
					return (res);
				free(res);
				return (NULL);
			}
		}
		c = buffer[(*pos)++];
		res = add_character(c, res, res_len++);
		if (c == '\n' || !res)
			break ;
	}
	return (res);
}
