/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:49:01 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/01 19:14:11 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"
#include <stdio.h>


void	print_matrix(char **arr)
{
	int i = 0;

	if (!arr)
		return;

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

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s map.cub\n", argv[0]);
		return (1);
	}
	init_game(&game);
	parse_cub_file(&game, argv[1]);
	init_player(&game);
	init_graphics(&game);
	mlx_loop_hook(game.mlx, render_frame,&game);
	mlx_loop(game.mlx);
	// print_config(&game.config);
	print_map(&game.map);
	return (0);
}
