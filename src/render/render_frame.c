/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:03:26 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/03 20:37:29 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static int	rgb(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

static void	draw_background(t_game *game)
{
	int				x;
	int				y;
	int	ceiling_color;
	int	floor_color;
	char			*pixel;
	int				bytes_per_pixel;
	int	color;

	bytes_per_pixel = game->bpp / 8;
	ceiling_color = rgb(game->config.ceiling);
	floor_color = rgb(game->config.floor);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		color = (y < SCREEN_HEIGHT / 2) ? ceiling_color : floor_color;
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			pixel = game->img_data + (y * game->line_len) + (x
					* bytes_per_pixel);
			*(unsigned int *)pixel = color;
			x++;
		}
		y++;
	}
}

static void	draw_wall_strip(t_game *game, t_ray *ray, int x)
{
	int				line_height;
	int				start;
	int				end;
	int				y;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	unsigned int	color;
	char			*tex_pixel;
	t_texture		*tex;
	double			perp_dist;
	int				tex_index;
	char			*pixel;

	double wall_x; // exact point of wall hit
	// 1. Calculate perpendicular distance to wall to avoid fish-eye
	perp_dist = (ray->side == 0) ? (ray->side_dist_x
			- ray->delta_x) : (ray->side_dist_y - ray->delta_y);
	line_height = (int)(SCREEN_HEIGHT / perp_dist);
	start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (end >= SCREEN_HEIGHT)
		end = SCREEN_HEIGHT - 1;
	// 2. Calculate exact wall hit coordinate (0.0 to 1.0)
	if (ray->side == 0)
		wall_x = game->player.y + perp_dist * ray->dir_y;
	else
		wall_x = game->player.x + perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	// 3. Determine texture index (0=NO,1=SO,2=WE,3=EA)
	if (ray->side == 0 && ray->dir_x > 0)
		tex_index = 1; // SO
	else if (ray->side == 0 && ray->dir_x < 0)
		tex_index = 0; // NO
	else if (ray->side == 1 && ray->dir_y > 0)
		tex_index = 3; // EA
	else
		tex_index = 2; // WE
	tex = &game->config.textures[tex_index];
	// 4. Calculate x coordinate on the texture
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	// 5. Calculate step to increase texture y coordinate per screen pixel
	step = 1.0 * tex->height / line_height;
	// 6. Starting texture y coordinate
	tex_pos = (start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
	y = start;
	while (y < end)
	{
		tex_y = ((int)tex_pos) % tex->height;
		if (tex_y < 0)
			tex_y = 0; // optional safety
		// get pointer to pixel color in texture img_data
		tex_pixel = tex->img_data + (tex_y * tex->line_len) + (tex_x * (tex->bpp
					/ 8));
		// read pixel color as unsigned int
		color = *(unsigned int *)tex_pixel;
		// write color to screen image buffer
		pixel = game->img_data + (y * game->line_len) + (x * (game->bpp / 8));
		*(unsigned int *)pixel = color;
		tex_pos += step;
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
