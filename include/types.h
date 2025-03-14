/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:14:25 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/03 15:14:26 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# ifndef MLX42_H
#  include "MLX42.h"
# endif

typedef enum e_errors
{
	FILE_NO_ARGS = 200,
	FILE_INVALID_EXTENSION,
	FILE_NO_OPEN,
	FILE_BYTES_READ,
	FILE_MISSING_PARAMS,
	IMG_FAILURE,
	TEXTURE_NO_PNG,
	TEXTURE_NO_OPEN,
	TEXTURE_FAILURE,
	MAP_MISSING_WALLS,
	MAP_INVALID_PATH,
	MAP_INVALID_FORMAT,
	MAP_NO_PLAYER,
	MAP_NO_START,
	MAP_UNKNOWN_CHARACTERS,
	MAP_TOO_MANY_PLAYERS,
	MAP_NOT_CLOSED,
	SYS_MALLOC,
}	t_errors;

typedef enum e_direction
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST,
	FLOOR,
	CEILING
}	t_direction;

typedef struct s_color
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;
}	t_color;

/**
 * TODO: Ignore the wall images, color data will be fetched from textures.
 * Wall pixel data will be placed onto a foreground image.
 */
typedef struct s_imgs
{
	mlx_image_t	*north;
	mlx_image_t	*east;
	mlx_image_t	*south;
	mlx_image_t	*west;
	mlx_image_t	*fg;
	mlx_image_t	*bg;
	uint32_t	floor;
	uint32_t	ceiling;
}	t_imgs;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
}	t_textures;

typedef struct s_level
{
	size_t			index;
	bool			loaded;
	char			**map;
	char			**map_copy;
	int				row_len;
	int				col_len;
	char			direction;
	int32_t			player_x;
	int32_t			player_y;
	t_imgs			imgs;
	t_textures		textures;
	mlx_t			**mlx;
	struct s_level	*next;
}	t_level;

typedef	struct s_player
{
	double	x;
	double	y;
	double	delta_x;
	double	delta_y;
	double	angle;
}	t_player;

typedef struct s_data
{
	mlx_t		*mlx;
	size_t		lvl_idx;
	t_level		*levels;
	t_player	player;
}	t_data;

typedef struct s_ray
{
	double	x;
	double	y;
	double	step_x;
	double	step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		delta_x;
	int		delta_y;
	int		side; // 0 for vertical, 1 for horizontal
}	t_ray;

#endif
