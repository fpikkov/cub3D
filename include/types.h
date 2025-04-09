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
	CEILING,
	DOOR1,
	DOOR2,
	DOOR3,
	DOOR4,
	DOOR5,
	DOOR6,
	DOOR7,
	EXIT1,
	EXIT2,
	EXIT3,
	EXIT4,
	EXIT5,
	EXIT6,
	EXIT7,
	MONSTER
}	t_direction;

typedef enum e_door_status
{
	CLOSED = 0,
	OPENING1,
	OPENING2,
	OPENING3,
	OPENING4,
	OPENING5,
	OPEN
}	t_door_status;

typedef enum e_shade
{
	NONE = 0,
	INCREASE,
	DECREASE
}	t_shade;

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
	mlx_texture_t	*door1;
	mlx_texture_t	*door2;
	mlx_texture_t	*door3;
	mlx_texture_t	*door4;
	mlx_texture_t	*door5;
	mlx_texture_t	*door6;
	mlx_texture_t	*door7;
	mlx_texture_t	*exit1;
	mlx_texture_t	*exit2;
	mlx_texture_t	*exit3;
	mlx_texture_t	*exit4;
	mlx_texture_t	*exit5;
	mlx_texture_t	*exit6;
	mlx_texture_t	*exit7;
	mlx_texture_t	*monster;
}	t_textures;

typedef struct s_door
{
	int			y;
	int			x;
	int			status;
	uint64_t	time;
}	t_door;

typedef struct s_exit
{
	int			y;
	int			x;
	int			status;
	uint64_t	time;
}	t_exit;

typedef	struct	s_monster
{
	int		y;
	int		x;
	uint64_t	time;
	bool		active;
	bool		move_down;
	bool		move_up;
	bool		move_right;
	bool		move_left;
}			t_monster;

typedef struct s_level
{
	size_t			index;
	bool			loaded;
	bool			has_doors;
	bool			has_monsters;
	bool			has_exit;
	char			**map;
	char			**map_copy;
	int				row_len;
	int				col_len;
	int				monster_count;
	char			direction;
	int32_t			player_x;
	int32_t			player_y;
	t_imgs			imgs;
	t_textures		textures;
	t_door			door;
	t_exit			exit;
	t_monster		monster[20];
	mlx_t			**mlx;
	struct s_data	*data;
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
	double		player_x;
	double		player_y;
	double		player_angle;
	float		tile_size;
	char		**map;
}	t_minimap;

typedef struct s_arrow
{
	int		center_x;
	int		center_y;
	int		tip_x;
	int		tip_y;
	int		left_x;
	int		left_y;
	int		right_x;
	int		right_y;
	int		back_x;
	int		back_y;
}	t_arrow;

typedef struct s_bresenham
{
	int		start_x;
	int		start_y;
	int		target_x;
	int		target_y;
	int		delta_x;
	int		delta_y;
	int		step_x;
	int		step_y;
	int		err;
	int		err2;
}	t_bresenham;

typedef struct s_torch
{
	bool		enabled;
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

typedef struct s_sprite_data
{
	float	hit_column;
	float	dist;
	int		x;
	int		y;
}	t_sprite_data;

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
	t_sprite_data	sprites[30];
	int			sprite_count;
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
