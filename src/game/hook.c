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
 */
void	game_hook(void *param)
{
	t_data	*data;
	t_level	*instance;

	data = (t_data *)param;
	instance = current_level(data);
	if (game_tick())
	{
		if (instance->has_monsters)
			monster_action(instance);
		if (instance->has_doors)
			move_door(instance);
		if (instance->has_exit)
			move_exit(instance);
		movement_handler(data, instance);
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
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_RELEASE)
		door_action(data);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
	{
		data->torch.enabled = !data->torch.enabled;
		data->torch.dark->enabled = !data->torch.dark->enabled;
		data->torch.light->enabled = !data->torch.light->enabled;
	}
}

void	mouse_hook(mouse_key_t b, action_t a, modifier_key_t m, void *p)
{
	t_data	*data;

	data = (t_data *)p;
	(void)m;
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_RELEASE)
	{
		data->torch.enabled = !data->torch.enabled;
		data->torch.dark->enabled = !data->torch.dark->enabled;
		data->torch.light->enabled = !data->torch.light->enabled;
	}
}
