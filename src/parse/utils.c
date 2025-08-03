/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:53:15 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/01 19:08:10 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line == '1' || *line == '0')
			return (1);
		else if (*line != ' ')
			return (0);
		line++;
	}
	return (0);
}

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
	game->bpp = 0;
	game->line_len = 0;
	game->endian = 0;
	game->config.no_path = NULL;
	game->config.so_path = NULL;
	game->config.we_path = NULL;
	game->config.ea_path = NULL;
	game->config.floor.r = -1;
	game->config.floor.g = -1;
	game->config.floor.b = -1;
	game->config.ceiling.r = -1;
	game->config.ceiling.g = -1;
	game->config.ceiling.b = -1;
	game->config.has_floor = 0;
	game->config.has_ceiling = 0;
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
