/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:50:28 by hshehab           #+#    #+#             */
/*   Updated: 2025/08/01 21:53:32 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	rgb_input_check(char *str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	if (commas > 2)
		return (0);
	return (1);
}

char	*replace_tabs_with_spaces(char *line)
{
	int		len;
	int		new_len;
	int		i;
	int		j;
	char	*new_line;

	len = strlen(line);
	new_len = 0;
	i = 0;
	while (i < len)
	{
		if (line[i] == '\t')
			new_len += 4;
		else
			new_len++;
		i++;
	}
	new_line = malloc(new_len + 1);
	if (new_line == NULL)
	{
		perror("Failed to allocate memory for new line");
		exit(EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (i < len)
	{
		if (line[i] == '\t')
		{
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
			new_line[j++] = ' ';
		}
		else
		{
			new_line[j++] = line[i];
		}
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}

void	parse_cub_file(t_game *game, char *filename)
{
	int		fd;
	int		map_started;
	char	*line;
	char	*line1;
	char	*line2;
	char	*line3;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("Error\nCannot open .cub file");
	map_started = 0;
	line1 = get_next_line(fd);
	while (line1)
	{
		line2 = replace_tabs_with_spaces(line1);
		free(line1);
		if (is_empty_line(line2))
		{
			free(line2);
			line1 = get_next_line(fd);
			continue ;
		}
		line3 = ft_strdup(line2);
		free(line2);
		if (!map_started && is_map_line(line3))
			map_started = 1;
		if (!map_started)
		{
			line = ft_strtrim(line3, " ");
			free(line3);
			parse_config_line(game, line);
			line = NULL;
			line1 = get_next_line(fd);
			continue ;
		}
		else
			append_map_line(&game->map, line3);
		free(line3);
		line1 = get_next_line(fd);
	}
	close(fd);
	if (!validate_config(&game->config) || !validate_map(&game->map)
		|| !validate_map1(&game->map))
	{
		free_given_file(game);
		exit(0);
	}
}

int	rgb_are_numbers(char **rgb)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 3;
	while (i < count)
	{
		j = 0;
		while (j < (int)ft_strlen(rgb[i]))
		{
			if (!ft_isdigit(rgb[i][j]))
			{
				if (i == 2 && rgb[i][(int)ft_strlen(rgb[i]) - 1] == '\n')
					return (1);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	has_xpm_extension(const char *filename)
{
	size_t	len;

	len = 0;
	while (filename[len] != '\0' && filename[len] != '\n')
		len++;
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".xpm", 4) == 0);
}

int	isDirection(char *str)
{
	return (!ft_strcmp(str, "NO") || !ft_strcmp(str, "SO") || !ft_strcmp(str,
			"WE") || !ft_strcmp(str, "EA"));
}

void	parse_config_line(t_game *game, char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (line)
		free(line);
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
	{
		free_matrix(tokens);
		free_given_file(game);
		perror("Error\nMissing or Additional Configuration Input");
		exit(EXIT_FAILURE);
	}
	if (isDirection(tokens[0]) && !has_xpm_extension(tokens[1]))
	{
		free_matrix(tokens);
		free_given_file(game);
		perror("Error\nWrong File Extension");
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(tokens[0], "NO") == 0)
	{
		if (game->config.no_path)
		{
			free_matrix(tokens);
			free_given_file(game);
			perror("Error\nDuplicate Found");
			exit(EXIT_FAILURE);
		}
		game->config.no_path = ft_strdup(tokens[1]);
	}
	else if (ft_strcmp(tokens[0], "SO") == 0)
	{
		if (game->config.so_path)
		{
			free_matrix(tokens);
			free_given_file(game);
			perror("Error\nDuplicate Found");
			exit(EXIT_FAILURE);
		}
		game->config.so_path = ft_strdup(tokens[1]);
	}
	else if (ft_strcmp(tokens[0], "WE") == 0)
	{
		if (game->config.we_path)
		{
			free_matrix(tokens);
			free_given_file(game);
			perror("Error\nDuplicate Found");
			exit(EXIT_FAILURE);
		}
		game->config.we_path = ft_strdup(tokens[1]);
	}
	else if (ft_strcmp(tokens[0], "EA") == 0)
	{
		if (game->config.ea_path)
		{
			free_matrix(tokens);
			free_given_file(game);
			perror("Error\nDuplicate Found");
			exit(EXIT_FAILURE);
		}
		game->config.ea_path = ft_strdup(tokens[1]);
	}
	else if (ft_strcmp(tokens[0], "F") == 0)
	{
		if (game->config.has_floor == 1)
		{
			free_matrix(tokens);
			free_given_file(game);
			perror("Error\nDuplicate Found");
			exit(EXIT_FAILURE);
		}
		parse_rgb(game, &game->config.floor, tokens[1], tokens);
		game->config.has_floor = 1;
	}
	else if (ft_strcmp(tokens[0], "C") == 0)
	{
		if (game->config.has_ceiling == 1)
		{
			free_matrix(tokens);
			free_given_file(game);
			perror("Error\nDuplicate Found");
			exit(EXIT_FAILURE);
		}
		parse_rgb(game, &game->config.ceiling, tokens[1], tokens);
		game->config.has_ceiling = 1;
	}
	else
	{
		free_matrix(tokens);
		free_given_file(game);
		perror("Error\nUnknown Identifier In Configuration");
		exit(EXIT_FAILURE);
	}
	free_matrix(tokens);
}

void	parse_rgb(t_game *game, t_color *color, char *str, char **tokens)
{
	char	**rgb;

	if (!rgb_input_check(str))
	{
		free_matrix(tokens);
		free_given_file(game);
		perror("Error\nInvalid RGB Input");
		exit(EXIT_FAILURE);
	}
	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_matrix(tokens);
		free_matrix(rgb);
		free_given_file(game);
		perror("Error\nInvalid RGB format");
		exit(EXIT_FAILURE);
	}
	if (!rgb_are_numbers(rgb))
	{
		free_matrix(tokens);
		free_matrix(rgb);
		free_given_file(game);
		perror("Error\nInput of RGB must be a number");
		exit(EXIT_FAILURE);
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
	{
		free_matrix(tokens);
		free_matrix(rgb);
		free_given_file(game);
		perror("Error\nRGB values must be in range 0–255");
		exit(EXIT_FAILURE);
	}
	free_matrix(rgb);
}

void	append_map_line(t_map *map, char *line)
{
	int		i;
	int		j;
	char	**new_grid;

	i = 0;
	j = 0;
	while (map->grid && map->grid[i])
		i++;
	new_grid = malloc(sizeof(char *) * (i + 2));
	if (!new_grid)
		perror("Error\nMemory allocation failed");
	while (j < i)
	{
		new_grid[j] = map->grid[j];
		j++;
	}
	new_grid[i] = ft_strdup(line);
	new_grid[i + 1] = NULL;
	free(map->grid);
	map->grid = new_grid;
	map->height++;
	if ((int)ft_strlen(line) > map->width)
		map->width = ft_strlen(line);
}

int	validate_config(t_config *config)
{
	if (!config->no_path || !config->so_path || !config->we_path
		|| !config->ea_path)
	{
		printf("Error\nMissing one or more texture paths");
		return (0);
	}
	if (!config->has_floor || !config->has_ceiling)
	{
		printf("Error\nMissing floor or ceiling color");
		return (0);
	}
	return (1);
}

int	validate_map(t_map *map)
{
	int		player_count;
	int		y;
	int		x;
	char	c;

	player_count = 0;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			c = map->grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			else if (c != '0' && c != '1' && c != ' ' && c != '\n')
			{
				printf("Error\nInvalid character in map");
				return (0);
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		printf("Error\nMap must contain exactly one player start");
		return (0);
	}
	return (1);
}
