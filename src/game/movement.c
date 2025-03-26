/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:03:43 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/10 12:03:45 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// TODO: Apply delta_time to magnitude which will enable smoother
// frame-independent movement.
// Additionally cap delta_time with fminf(delta_time, MOVE_SPEED)
// to avoid large jumps when frame pacing slows down.
static void	normalize_vectors(float	*x, float *y)
{
	float	magnitude;
	float	delay;

	magnitude = hypotf((*x), (*y));
	delay = frame_delay();
	if (magnitude > 0)
	{
		*x = ((*x) / magnitude) * (MOVE_SPEED + delay); // Adding small increment to the original speed
		*y = ((*y) / magnitude) * (MOVE_SPEED + delay);
	}
}

static void	apply_movement(t_player *p, t_level *lvl, float x, float y)
{
	float	target_x;
	float	target_y;

	target_x = p->x + x + BOUNDARY;
	if (x < 0)
		target_x = p->x + x - BOUNDARY;
	target_y = p->y + y + BOUNDARY;
	if (y < 0)
		target_y = p->y + y - BOUNDARY;
	if (!is_wall(lvl, target_x, p->y))
		p->x += x;
	if (!is_wall(lvl, p->x, target_y))
		p->y += y;
}

static void	sum_direction_vectors(t_data *data, float *x, float *y)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		*x += data->player.dir_x;
		*y += data->player.dir_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		*x -= data->player.dir_x;
		*y -= data->player.dir_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		*x += data->player.right_x;
		*y += data->player.right_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		*x -= data->player.right_x;
		*y -= data->player.right_y;
	}
}

/**
 * @brief Will normalize the sum of all directional vectors,
 * then check if the intended direction is not a wall before
 * applying the movement to the player.
 */
void	movement_handler(t_data *data, t_level *lvl)
{
	float	total_x;
	float	total_y;

	if (!lvl->loaded)
		return ;
	total_x = 0;
	total_y = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(&data->player);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(&data->player);
	sum_direction_vectors(data, &total_x, &total_y);
	normalize_vectors(&total_x, &total_y);
	apply_movement(&data->player, lvl, total_x, total_y);
}
