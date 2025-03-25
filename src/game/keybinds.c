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

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
}

void	movement_handler(t_data *data, t_level *lvl)
{
	if (!lvl->loaded)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_forward(&data->player, lvl);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_backward(&data->player, lvl);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(&data->player, lvl);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(&data->player, lvl);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(&data->player);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(&data->player);
}
