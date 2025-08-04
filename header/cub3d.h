/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:38:23 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/04 14:42:04 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../getnextline/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef DEFINES_H
#  define DEFINES_H

#  define SCREEN_WIDTH 800
#  define SCREEN_HEIGHT 700
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#define MAX_KEYS 256

#  define COLOR_FLOOR 0x222222
#  define COLOR_CEILING 0x888888

#  define MOVE_SPEED 0.07
#  define ROT_SPEED 0.07
# endif

typedef struct s_keys
{
    int w;      // forward
    int s;      // backward  
    int a;      // left
    int d;      // right
    int left;   // rotate left
    int right;  // rotate right
    int esc;    // escape
} t_keys;
// ----------------------
// RGB Color
// ----------------------
typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;
// ----------------------
// Texture Info (XPM images)
// ----------------------
typedef struct s_texture
{
	void		*img_ptr;
	char		*img_data;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_texture;
// ----------------------
// Configuration Info from .cub
// ----------------------
typedef struct s_config
{
	char *no_path; // done
	char *so_path; // done
	char *we_path; // done
	char *ea_path; // done
	t_texture	textures[4];
	t_color floor;   // done
	t_color ceiling; // done
	int has_floor;   // done
	int has_ceiling; // done
}				t_config;
// ----------------------
// Map Data
// ----------------------
typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;
// ----------------------
// Player Info
// ----------------------
typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;
// ----------------------
// Raycasting & Game State
// ----------------------
typedef struct s_game
{
	void *mlx; // done
	void *win; // done
	void		*img;
	char		*img_data;
	int			bpp;
	int			line_len;
	int endian; // done
	t_config	config;
	t_map map;       // done
	t_player player; // done
	t_keys  keys;
}				t_game;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_x;
	double		delta_y;
	int			side;
}				t_ray;



int				ft_strcmp(char *s1, char *s2);
void			free_matrix(char **matrix);
void			init_game(t_game *game);
void			print_map(t_map *map);
void			init_player(t_game *game);
void			init_graphics(t_game *game);
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
void			free_game(t_game *game);
void			error_exit(char *s);
int				render_frame(void *param);
void			free_given_file(t_game *game);
void			print_matrix(char **arr);
void			debug_write(char *str);

int	close_window(t_game *game);
#endif