/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:12:40 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/07 12:12:42 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * TODO: If exit is reached, draw the images from the next level node
 * TODO: Keep track of level changes and cleanup previous images
 * before changing the level
 */

void	move_door(t_level *instance)
{
	if (get_time() - instance->door.time >= 200)
	{
		if (instance->door.status == OPENING1)
			instance->map[instance->door.y][instance->door.x] = '3';
		else if (instance->door.status == OPENING2)
			instance->map[instance->door.y][instance->door.x] = '4';
		else if (instance->door.status == OPENING3)
			instance->map[instance->door.y][instance->door.x] = '5';
		else if (instance->door.status == OPENING4)
			instance->map[instance->door.y][instance->door.x] = '6';
		else if (instance->door.status == OPENING5)
			instance->map[instance->door.y][instance->door.x] = '7';
		if (instance->door.status == OPEN)
		{
			instance->map[instance->door.y][instance->door.x] = '8';
			ft_memset(&instance->door, 0, sizeof(t_door));
		}
		else
		{
			instance->door.status++;
			instance->door.time = get_time();
		}
	}
}

void	game_hook(void *param)
{
	t_data	*data;
	t_level	*instance;

	data = (t_data *)param;
	instance = current_level(data);
	if (game_tick())
	{
		movement_handler(data, instance);
		if (instance->door.status > CLOSED)
			move_door(instance);
		render_surfaces(instance, &data->player);
		update_minimap(data, instance);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
	if ((keydata.key == MLX_KEY_M || keydata.key == MLX_KEY_TAB) \
	&& keydata.action == MLX_RELEASE)
		data->minimap.img->enabled = !data->minimap.img->enabled;
	if (keydata.key == MLX_KEY_N && keydata.action == MLX_RELEASE \
	&& keydata.modifier == MLX_CONTROL)
		next_level(data);
}
