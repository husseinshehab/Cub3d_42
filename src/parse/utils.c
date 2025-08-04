/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:53:15 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/03 20:36:46 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"


int	ft_strcmp(char *s1,char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	init_game(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->img_data = NULL;
	game->bpp = 32;
	game->line_len = 0;
	game->endian = 0;
	game->config.no_path = ft_strdup("./wall1.xpm");
    game->config.so_path = ft_strdup("./wall2.xpm");
    game->config.we_path = ft_strdup("./wall3.xpm");
    game->config.ea_path = ft_strdup("./wall4.xpm");
	game->config.floor.r = 244;
	game->config.floor.g = 190;
	game->config.floor.b = 118;
	game->config.ceiling.r = 230;
	game->config.ceiling.g = 150;
	game->config.ceiling.b = 100;
	game->config.has_floor = 1;
	game->config.has_ceiling = 1;
	i = 0;
	while (i < 4)
	{
		game->config.textures[i].img_ptr = NULL;
		game->config.textures[i].img_data = NULL;
		game->config.textures[i].width = 0;
		game->config.textures[i].height = 0;
		game->config.textures[i].bpp = 0;
		game->config.textures[i].line_len = 0;
		game->config.textures[i].endian = 0;
		i++;
	}
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
}
