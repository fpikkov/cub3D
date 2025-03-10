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
void	game_hook(void *param)
{
	t_data	*data;
	t_level	*instance;

	data = (t_data *)param;
	instance = data->levels;
	while (instance->index != data->lvl_idx && instance->next)
		instance = instance->next;
	if (game_tick())
		render_surfaces(instance, &data->player);
}
