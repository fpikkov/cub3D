/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:55:57 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/07 11:55:59 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * TODO: Wall collision by checking if player is some units away from wall
 */
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	t_level	*instance;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
	instance = current_level(data);
	if (!instance->loaded)
		return ;
	if (input_tick())
	{
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT)
			move_forward(&data->player, instance);
		else if (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT)
			move_backward(&data->player, instance);
		else if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT)
			move_right(&data->player, instance);
		else if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT)
			move_left(&data->player, instance);
		else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT)
			rotate_left(&data->player);
		else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT)
			rotate_right(&data->player);
		if (DEBUG)
			printf("pX:%.2f pY;%.2f | pA: %.2f\n", \
			data->player.x, data->player.y, data->player.angle);
	}
}
