/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouselook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:27:17 by fpikkov           #+#    #+#             */
/*   Updated: 2025/04/28 12:27:19 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Unlocks the mouse from the game window
 */
void	mouselook_switch(t_data *data)
{
	data->mouse_unlock = !data->mouse_unlock;
	if (data->mouse_unlock)
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	else
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
}

/**
 * @brief Initializes mouse by setting it's position to the middle
 * of the screen and hides the cursor.
 */
void	init_mouse(t_data *data)
{
	mlx_set_mouse_pos(data->mlx, W_WIDTH / 2, W_HEIGHT / 2);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_mouse_hook(data->mlx, mouse_hook, data);
}
