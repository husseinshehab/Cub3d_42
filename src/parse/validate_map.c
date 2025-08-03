/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 22:36:12 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/01 21:52:33 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_fillable(char c)
{
	return (c == '0' || is_player_char(c));
}

static char	**copy_map(char **src, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	print_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
	{
		printf("Matrix is NULL.\n");
		return ;
	}
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

static int	flood_fill(char **map, int x, int y, int height, int width)
{
	if (x < 0 || y < 0 || y >= height)
		return (0);
	if (x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (!is_fillable(map[y][x]))
		return (1);
	map[y][x] = 'F';
	if (!flood_fill(map, x + 1, y, height, width))
		return (0);
	if (!flood_fill(map, x - 1, y, height, width))
		return (0);
	if (!flood_fill(map, x, y + 1, height, width))
		return (0);
	if (!flood_fill(map, x, y - 1, height, width))
		return (0);
	return (1);
}

int	validate_map1(t_map *map)
{
	char	**copy;
	int		result;
	int		x;
	int		y;

	result = 1;
	copy = copy_map(map->grid, map->height);
	if (!copy)
		return (0);
	y = 0;
	print_char_matrix(copy);
	while (y < map->height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->grid[y]))
		{
			if (is_fillable(copy[y][x]))
			{
				result = flood_fill(copy, x, y, map->height, map->width);
				if (result == 0)
				{
					free_matrix(copy);
					printf("Error\nMap is not closed");
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	free_matrix(copy);
	return (1);
}
