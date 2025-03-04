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

# include "MLX42.h"

typedef enum e_errors
{
	FILE_NO_ARGS = 200,
	FILE_MULTIPLE_ARGS,
	FILE_INVALID_EXTENSION,
	FILE_NO_OPEN,
	FILE_BYTES_READ,
	FILE_MISSING_PARAMS,
	TEXTURE_DUPLICATE,
	TEXTURE_NO_OPEN,
	TEXTURE_FAILURE,
	MAP_MISSING_WALLS,
	MAP_INVALID_PATH,
	MAP_INVALID_FORMAT,
	MAP_NO_PLAYER,
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

typedef union u_color
{
	struct
	{
		uint8_t	red;
		uint8_t	green;
		uint8_t	blue;
		uint8_t	alpha;
	}			s_col;
	uint32_t	value;
}				t_color;

typedef struct s_imgs
{
	mlx_image_t	*north;
	mlx_image_t	*east;
	mlx_image_t	*south;
	mlx_image_t	*west;
	t_color		floor;
	t_color		ceiling;
}	t_imgs;

typedef struct s_data
{
	mlx_t	*mlx;
	t_imgs	imgs;

}	t_data;

#endif
