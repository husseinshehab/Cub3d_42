/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:01 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/04 14:41:04 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	get_longest_line_len(char **matrix)
{
	int	max_len;
	int	len;
	int	i;

	max_len = 0;
	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
	{
		len = strlen(matrix[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

int	get_matrix_height(char **matrix)
{
	int	height;

	height = 0;
	if (!matrix)
		return (0);
	while (matrix[height])
		height++;
	return (height);
}

int	initialize_game_map(t_game *game)
{
	const char	*map_data[] = {"        1111111111111111111111111    ",
			"        1000000000110000000E00001    ",
			"        1011000000000000000000001    ",
			"        1001000000000000001000001    ",
			"111111111101100000111000000000001    ",
			"100000000011000000000000000001111    ",
			"11110111111111000000000000001        ",
			"11110111111111011101010010001        ",
			"11000000110101000000000010001        ",
			"10000000000000001100000000001        ",
			"10000000000000001101010010001        ",
			"11000001110101011111011110001        ",
			"11110111 1110101 101111010001        ",
			"11111111 1111111 111111111111        ", NULL};
	int			row_count;

	row_count = 0;
	while (map_data[row_count])
		row_count++;
	game->map.grid = malloc((row_count + 1) * sizeof(char *));
	if (!game->map.grid)
		return (1); // allocation failed
	for (int i = 0; i < row_count; i++)
	{
		game->map.grid[i] = ft_strdup(map_data[i]);
		if (!game->map.grid[i])
		{
			// cleanup if any strdup fails
			for (int j = 0; j < i; j++)
				free(game->map.grid[j]);
			free(game->map.grid);
			return (1);
		}
	}
	game->map.grid[row_count] = NULL;
	game->map.width = get_longest_line_len(game->map.grid);
	game->map.height = get_matrix_height(game->map.grid);
	return (0);
}

void	print_matrix(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
void	print_config(t_config *config)
{
	printf("Texture Paths:\n");
	printf("NO: %s\n", config->no_path);
	printf("SO: %s\n", config->so_path);
	printf("WE: %s\n", config->we_path);
	printf("EA: %s\n", config->ea_path);
	printf("Floor Color: %d,%d,%d\n", config->floor.r, config->floor.g,
		config->floor.b);
	printf("Ceiling Color: %d,%d,%d\n", config->ceiling.r, config->ceiling.g,
		config->ceiling.b);
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	printf("Map (%d lines):\n", map->height);
	printf("----------------------\n");
	while (map->grid && map->grid[i])
	{
		printf("%s\n", map->grid[i]);
		i++;
	}
	printf("----------------------\n");
}
void debug_write(char *str)
{
	int length = ft_strlen(str);
	write(1,str,length);
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argv;
	(void)argc;
	
	init_game(&game);

	initialize_game_map(&game);
	init_player(&game);
	init_graphics(&game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
