/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:16:41 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/03 20:50:08 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"


int load_textures(t_game *game)
{
    char *paths[4] = {
        game->config.no_path,
        game->config.so_path,
        game->config.we_path,
        game->config.ea_path
    };

    for (int i = 0; i < 4; i++)
    {
		
        game->config.textures[i].img_ptr = mlx_xpm_file_to_image(
            game->mlx,
            paths[i],
            &game->config.textures[i].width,
            &game->config.textures[i].height
        );
        if (!game->config.textures[i].img_ptr)
            return (1); // failed to load

        game->config.textures[i].img_data = mlx_get_data_addr(
            game->config.textures[i].img_ptr,
            &game->config.textures[i].bpp,
            &game->config.textures[i].line_len,
            &game->config.textures[i].endian
        );
        if (!game->config.textures[i].img_data)
            return (1);
		
    }
    return (0);
}
void draw_texture_debug(t_game *game)
{
	for (int i = 0; i < 4; i++)
	{
		t_texture *tex = &game->config.textures[i];
		if (!tex->img_ptr)
			error_exit("Error: Missing texture image");

		int row = i / 2;
		int col = i % 2;
		int x = col * tex->width;
		int y = row * tex->height;

		mlx_put_image_to_window(game->mlx, game->win, tex->img_ptr, x, y);
	}
}


int	close_window(t_game *game)
{
	if (game->img)
		free_game(game);
	exit (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
		rotate_right(game);
	else if (keycode == KEY_RIGHT)
		rotate_left(game);
	return (0);
}

void	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Error\nmlx_init failed");

	if (load_textures(game))
		error_exit("Error\nFailed to load textures");

	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game->win)
		error_exit("Error\nWindow creation failed");

	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
		error_exit("Error\nImage buffer creation failed");

	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->line_len, &game->endian);
	if (!game->img_data || game->line_len <= 0 || game->bpp <= 0)
		error_exit("Failed to get image data address");

	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);

	// ⬇️ Show the north wall texture just to confirm it's working
	draw_texture_debug(game);
}

