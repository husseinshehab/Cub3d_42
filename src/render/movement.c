/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:18:26 by hshehab           #+#    #+#             */
/*   Updated: 2025/07/31 12:37:22 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	move_forward(t_game *game)
{
	double	move_speed;

	move_speed = MOVE_SPEED;
	if (game->map.grid[(int)(game->player.y)][(int)(game->player.x
			+ game->player.dir_x * move_speed)] != '1')
		game->player.x += game->player.dir_x * move_speed;
	if (game->map.grid[(int)(game->player.y + game->player.dir_y
			* move_speed)][(int)(game->player.x)] != '1')
		game->player.y += game->player.dir_y * move_speed;
}

void	move_backward(t_game *game)
{
	double	move_speed;

	move_speed = MOVE_SPEED;
	if (game->map.grid[(int)(game->player.y)][(int)(game->player.x
			- game->player.dir_x * move_speed)] != '1')
		game->player.x -= game->player.dir_x * move_speed;
	if (game->map.grid[(int)(game->player.y - game->player.dir_y
			* move_speed)][(int)(game->player.x)] != '1')
		game->player.y -= game->player.dir_y * move_speed;
}

void	move_left(t_game *game)
{
	double	move_speed;
	double	px;
	double	py;

	move_speed = MOVE_SPEED;
	px = game->player.plane_x;
	py = game->player.plane_y;
	if (game->map.grid[(int)(game->player.y)][(int)(game->player.x - px
			* move_speed)] != '1')
		game->player.x -= px * move_speed;
	if (game->map.grid[(int)(game->player.y - py
			* move_speed)][(int)(game->player.x)] != '1')
		game->player.y -= py * move_speed;
}

void	move_right(t_game *game)
{
	double	move_speed;
	double	px;
	double	py;

	move_speed = MOVE_SPEED;
	px = game->player.plane_x;
	py = game->player.plane_y;
	if (game->map.grid[(int)(game->player.y)][(int)(game->player.x + px
			* move_speed)] != '1')
		game->player.x += px * move_speed;
	if (game->map.grid[(int)(game->player.y + py
			* move_speed)][(int)(game->player.x)] != '1')
		game->player.y += py * move_speed;
}
