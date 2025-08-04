/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:48:51 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/04 13:59:35 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	helper(t_game *game)
{
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = -0.66;
}

//hole kermel to point in the direction the player 
//is facing and the plane define the 2d plane
//perpendicular to the direction vector and the player FOV(field of view)
void	set_player_orientation(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (dir == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (dir == 'W')
		helper(game);
}

// 	+ 0.5 kermel ma tbayin in the center of the 
//	tile. (3,2) top left of this cell while (3.5,
// 	2.5) bteje b center
void	init_player(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			c = game->map.grid[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				set_player_orientation(game, c);
				game->map.grid[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
