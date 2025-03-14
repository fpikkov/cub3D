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
		if (lvl->imgs.fg)
			mlx_image_to_window(*lvl->mlx, lvl->imgs.fg, 0, 0);
		lvl->loaded = true;
	}
}

/**
 * @brief Returns the encoded color value from x and y position of the texture.
 * @return color value in uint32_t format
 */
static uint32_t	get_pixel(mlx_texture_t	*tex, uint32_t x, uint32_t y)
{
	uint32_t	col;
	uint8_t		*ptr;

	col = 0;
	ptr = tex->pixels + (x * y * tex->bytes_per_pixel);
	col |= *ptr << 24;
	ptr++;
	col |= *ptr << 16;
	ptr++;
	col |= *ptr << 8;
	ptr++;
	col |= *ptr;
	return (col);
}

/**
 * TODO: Take in the side of wall which was hit (pass correect tex to get_pixel)
 * TODO: y scales from 0 to factor (scaled height), this will require an offset
 * TODO: Make sure you're not dividing by 0
 */
static void	draw_wall_to_fg(t_level *lvl, double distance, double angle)
{
	uint32_t	factor;
	uint32_t	color;
	uint32_t	screen_x;
	uint32_t	x;
	uint32_t	y;
	uint32_t	i;

	screen_x = ((angle + (to_radian(FOV) / 2)) / to_radian(FOV)) * W_WIDTH;
	x = (angle / to_radian(FOV)) * TILE;
	factor = W_HEIGHT / distance;
	i = 0;
	while (i < factor)
	{
		y = (i / factor) * TILE;
		color = get_pixel(lvl->textures.north, x, y);
		mlx_put_pixel(lvl->imgs.fg, screen_x, y, color);
		i++;
	}
}

/**
 * TODO: Test function for drawing wall images on the screen
 * TODO: Ray distance is an extreme value, please fix
 */
static void	draw_walls(t_level *lvl, t_player *p)
{
	double	dist;
	double	offset;

	offset = 0.0;
	// Cast ray for each degree within FOV
	dist = raycast(lvl, p, p->angle);

	//printf("distance: %f\n", dist);
	// Put image to window: W_HEIGHT / ray_distance (if dist > 0)
	if (dist > 0.0)
	{
		while (offset < (PI / 2))
		{
			draw_wall_to_fg(lvl, dist, p->angle + offset);
			offset += DEGREE * 10;
		}
	}
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
