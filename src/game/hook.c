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
 * TODO: Drawing images should happen every 1.6 milliseconds, thus requiring
 * the drawing to be in a game hook
 */
static void	draw_images(t_level *lvl)
{
	mlx_image_to_window(*lvl->mlx, lvl->imgs.floor, 0, W_HEIGHT / 2);
	mlx_image_to_window(*lvl->mlx, lvl->imgs.ceiling, 0, 0);
}

/**
 * If exit is reached, draw the images from the next level node
 */
void	game_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (game_tick())
		draw_images(data->levels);
}
