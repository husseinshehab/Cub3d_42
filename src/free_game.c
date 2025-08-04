/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:45:22 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/03 20:58:57 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	error_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	free_given_file(t_game *game)
{
	if (game->config.no_path)
		free(game->config.no_path);
	if (game->config.so_path)
		free(game->config.so_path);
	if (game->config.we_path)
		free(game->config.we_path);
	if (game->config.ea_path)
		free(game->config.ea_path);
	if (game->map.grid)
		free_matrix(game->map.grid);
}

void	free_game(t_game *game)
{
	int	i;

	// Free texture paths
	if (game->config.no_path)
		free(game->config.no_path);
	if (game->config.so_path)
		free(game->config.so_path);
	if (game->config.we_path)
		free(game->config.we_path);
	if (game->config.ea_path)
		free(game->config.ea_path);
	// Free map grid
	if (game->map.grid)
		free_matrix(game->map.grid);
	// Destroy texture images
	i = 0;
	while (i < 4)
	{
		if (game->config.textures[i].img_ptr)
			mlx_destroy_image(game->mlx, game->config.textures[i].img_ptr);
		i++;
	}
	// Destroy main image
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	// Destroy window
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	// Destroy MLX display connection (this is the key addition)
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

// Alternative cleanup function for emergency exits
void	cleanup_and_exit(t_game *game, char *error_msg, int exit_code)
{
	if (error_msg)
		fprintf(stderr, "Error: %s\n", error_msg);
	if (game)
		free_game(game);
	exit(exit_code);
}
