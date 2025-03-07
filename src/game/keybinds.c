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
 * TODO: Player movement and rotation
 * TODO: Update after each tick (1.6 milliseconds)
 * TODO: Reset player x and y when changing maps
 * TODO: Wall collision by checking if player is some units away from wall
 */
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data			*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		/* Player movement*/;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		/* Player movement*/;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		/* Player movement*/;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		/* Player movement*/;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		/* Player looks left*/;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		/* Player looks right*/;;
}
