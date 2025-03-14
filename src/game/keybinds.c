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
 * @brief Checks if the current level instance has been loaded
 * @return true if loaded, otherwise false
 */
static bool	is_loaded(t_data *data)
{
	t_level	*instance;

	instance = data->levels;
	while (instance->index != data->lvl_idx && instance->next)
		instance = instance->next;
	if (instance->loaded)
		return (true);
	return (false);
}

/**
 * TODO: Wall collision by checking if player is some units away from wall
 */
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data			*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
	if (!is_loaded(data))
		return ;
	if (input_tick())
	{
		if (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT)
			move_forward(&data->player);
		else if (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT)
			move_backward(&data->player);
		else if (keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT)
			move_right(&data->player);
		else if (keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT)
			move_left(&data->player);
		else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT)
			rotate_left(&data->player);
		else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT)
			rotate_right(&data->player);
	}
}
