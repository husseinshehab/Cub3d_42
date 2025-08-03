/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:31:19 by hshehab           #+#    #+#             */
/*   Updated: 2025/03/22 12:27:38 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

struct	s_hw
{
	int	width;
	int	height;
};

char	*get_next_line(int fd);
char	*read_from_file(int fd, char *buffer, int *size, int *pos);
char	*add_character(char c, char *res, int res_len);
size_t	read_from_file_new(int fd, char *buffer, int *new_size, int*pos);

#endif
