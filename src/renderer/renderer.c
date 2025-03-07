/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:55:14 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/07 15:55:16 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	render_floor(t_level *lvl)
{
	if (lvl->loaded == false)
	{
		if (lvl->imgs.floor)
			mlx_image_to_window(*lvl->mlx, lvl->imgs.floor, 0, W_HEIGHT / 2);
		if (lvl->imgs.ceiling)
			mlx_image_to_window(*lvl->mlx, lvl->imgs.ceiling, 0, 0);
		lvl->loaded = true;
	}
}

/**
 * TODO: Implement raycasting features so we know how far to render walls
 */
void	render_surfaces(t_level *lvl)
{
	new_images(lvl);
	render_floor(lvl);
}
