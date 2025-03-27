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
	LAUNCH_PATH,
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

typedef struct s_imgs
{
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

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	dir_x;
	float	dir_y;
	float	right_x;
	float	right_y;
}	t_player;

typedef struct s_minimap
{
	mlx_image_t	*img;
	int			width;
	int			height;
	int			start_x;
	int			start_y;
	int			player_x;
	int			player_y;
	float		tile_size;
	char		**map;
}	t_minimap;

typedef struct s_torch
{
	mlx_image_t	*dark;
	mlx_image_t	*light;
}	t_torch;

typedef struct s_data
{
	mlx_t		*mlx;
	size_t		lvl_idx;
	t_level		*levels;
	t_player	player;
	t_minimap	minimap;
	t_torch		torch;
}	t_data;

typedef struct s_ray
{
	t_direction	wall_type;
	float		distance;
	float		hit_column;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	float		side_dist_x;
	float		side_dist_y;
	float		delta_dist_x;
	float		delta_dist_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	float		camera_x;
}	t_ray;

typedef struct s_line
{
	float	height;
	float	start;
	float	end;
	float	current;
	float	delta;
}	t_line;

#endif
