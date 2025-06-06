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
 * NOTE: Keep render surfaces at the top of the hook calls as level
 * initialization depends on it.
 *
 * @brief Main game hook of the game which handles movement and rendering
 */
void	game_hook(void *param)
{
	t_data	*data;
	t_level	*instance;

	data = (t_data *)param;
	instance = current_level(data);
	if (game_tick())
	{
		render_surfaces(instance, &data->player);
		movement_handler(data, instance);
		update_minimap(data, instance);
		monster_action(instance);
		if (instance->has_doors)
			move_door(instance);
		if (instance->has_exit)
			open_exit(instance);
		flashlight_battery(&data->torch);
		if (instance->map[instance->player_y][instance->player_x] == 'P'
			&& instance->exit.status == OPEN)
			next_level(data);
		else if (instance->player_dead)
		{
			printf("Spookieman caught you, GAME OVER\n");
			mlx_close_window(data->mlx);
		}
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
		if (data->torch.battery != 0)
			flashlight_switch(&data->torch);
	if (keydata.key == MLX_KEY_U && keydata.action == MLX_RELEASE)
		mouselook_switch(data);
}

void	mouse_hook(mouse_key_t b, action_t a, modifier_key_t m, void *p)
{
	t_data	*data;

	data = (t_data *)p;
	(void)m;
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_RELEASE)
		if (data->torch.battery != 0)
			flashlight_switch(&data->torch);
}
