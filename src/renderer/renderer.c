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

/**
 * @brief Renders the floor and ceiling and initializes player position.
 * This function will initialize the loading of a new level.
 */
static void	level_setup(t_level *lvl, t_player *p)
{
	if (lvl->loaded == false)
	{
		init_level_params(lvl, p);
		if (lvl->imgs.bg)
			mlx_image_to_window(*lvl->mlx, lvl->imgs.bg, 0, 0);
		lvl->loaded = true;
	}
}

/**
 * TODO: Test function for drawing wall images on the screen
 */
static void	draw_walls(t_level *lvl, t_player *p)
{
	double	dist;

	// Cast ray for each degree within FOV
	dist = raycast(lvl, p, p->angle);

	// Put image to window: W_HEIGHT / ray_distance (if dist > 0)
	if (dist > 0.0)
	{
		//mlx_resize_image(lvl->imgs.north, (uint32_t)(TILE / dist), (uint32_t)(TILE / dist));
		//mlx_image_to_window(*lvl->mlx, lvl->imgs.north, (W_WIDTH - lvl->imgs.north->width) / 2, (W_HEIGHT - lvl->imgs.north->height) / 2);
		mlx_image_to_window(*lvl->mlx, lvl->imgs.north, (W_WIDTH - TILE) / 2, (W_HEIGHT / dist));
	}
	//printf("Dist: %f\n	P_angle: %f\n", dist, p->angle);
}

/**
 * @brief The main function which gets called when rendering a new frame
 */
void	render_surfaces(t_level *lvl, t_player *p)
{
	new_images(lvl);
	level_setup(lvl, p);
	draw_walls(lvl, p);
}
