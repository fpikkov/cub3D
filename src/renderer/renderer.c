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

static void	line_init(t_line *line, t_ray *ray)
{
	line->height = floor(W_HEIGHT / ray->distance);
	line->start = (-line->height / 2) + (W_HEIGHT / 2);
	line->end = (line->height / 2) + (W_HEIGHT / 2);
	line->delta = line->end - line->start;
	if (line->delta == 0)
		line->delta++;
	line->current = line->start;
}

/**
 * @brief Returns the color data for the current wall we're drawing
 */
static uint32_t	select_texture(t_ray *ray, t_level *lvl, int y)
{
	uint32_t	color;

	color = 0x0;
	if (ray->wall_type == NORTH)
		color = nearest_neighbor(lvl->textures.north, (int)ray->hit_column, y);
	else if (ray->wall_type == EAST)
		color = nearest_neighbor(lvl->textures.east, (int)ray->hit_column, y);
	else if (ray->wall_type == SOUTH)
		color = nearest_neighbor(lvl->textures.south, (int)ray->hit_column, y);
	else if (ray->wall_type == WEST)
		color = nearest_neighbor(lvl->textures.west, (int)ray->hit_column, y);
	return (color);
}

/**
 * @brief Draws vertical line onto the screen x position based on how far
 * the ray hit the wall on the map. The image size gets interpolated so pixel
 * data is always fetched from a square range defined by the TILE constant.
 * @param[in] ray the casted ray struct
 * @param[in] lvl the current level
 * @param[in] x the horizontal screen coordinate
 */
static void	draw_line(t_ray *ray, t_level *lvl, int x)
{
	t_line		line;
	int			scaled_y;
	uint32_t	color;

	ft_memset(&line, 0, sizeof(t_line));
	line_init(&line, ray);
	color = 0;
	while (line.current <= line.end)
	{
		if (line.current < 0)
			line.current = 0;
		if (line.current >= W_HEIGHT)
			break ;
		if (line.current >= 0 && line.current < W_HEIGHT)
		{
			scaled_y = (int)floor(((line.current - line.start) \
			* (TILE - 1)) / line.delta);
			color = select_texture(ray, lvl, scaled_y);
			mlx_put_pixel(lvl->imgs.fg, x, (int)line.current, color);
		}
		line.current++;
	}
}

/**
 * @brief Draws walls line by line to the foreground image
 */
static void	draw_foreground(t_level *lvl, t_player *p)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < W_WIDTH)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		if (raycast(&ray, lvl, p, x))
			draw_line(&ray, lvl, x);
		x++;
	}
}

/**
 * @brief The main function which gets called when rendering a new frame
 */
void	render_surfaces(t_level *lvl, t_player *p)
{
	level_setup(lvl, p);
	reset_foreground(lvl);
	draw_foreground(lvl, p);
}
