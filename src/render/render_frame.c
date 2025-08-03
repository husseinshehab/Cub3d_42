/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:03:26 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/01 19:59:22 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static int	rgb(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

static void	draw_background(t_game *game)
{
	int		x;
	int		y;
	int		color;
	char	*pixel;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		color = (y < SCREEN_HEIGHT
				/ 2) ? rgb(game->config.ceiling) : rgb(game->config.floor);
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			pixel = game->img_data + (y * game->line_len) + (x * (game->bpp
						/ 8));
			if (pixel >= game->img_data + game->line_len * SCREEN_HEIGHT)
				error_exit("Image write overflow");
			*(unsigned int *)pixel = color;
			x++;
		}
		y++;
	}
}

static void	draw_wall_strip(t_game *game, t_ray *ray, int x)
{
	double	perp_dist;
	int		line_height;
	int		start;
	int		end;
	int		y;
	int		color;
	char	*pixel;

	if (ray->side == 0)
		perp_dist = ray->side_dist_x - ray->delta_x;
	else
		perp_dist = ray->side_dist_y - ray->delta_y;
	line_height = (int)(SCREEN_HEIGHT / perp_dist);
	start = -line_height / 2 + SCREEN_HEIGHT / 2;
	end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (start < 0)
		start = 0;
	if (end >= SCREEN_HEIGHT)
		end = SCREEN_HEIGHT - 1;
	color = (ray->side == 0) ? 0x0010FF : 0x110F00;
	y = start;
	while (y < end)
	{
		pixel = game->img_data + (y * game->line_len) + (x * (game->bpp / 8));
		*(unsigned int *)pixel = color;
		y++;
	}
}

static void	perform_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

static void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	ray->step_x = (ray->dir_x < 0) ? -1 : 1;
	ray->side_dist_x = (ray->dir_x < 0) ? (game->player.x - ray->map_x)
		* ray->delta_x : (ray->map_x + 1.0 - game->player.x) * ray->delta_x;
	ray->step_y = (ray->dir_y < 0) ? -1 : 1;
	ray->side_dist_y = (ray->dir_y < 0) ? (game->player.y - ray->map_y)
		* ray->delta_y : (ray->map_y + 1.0 - game->player.y) * ray->delta_y;
}

int	render_frame(void *param)
{
	t_game	*game;
	int		x;
	t_ray	ray;

	game = (t_game *)param;
	draw_background(game);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		draw_wall_strip(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
