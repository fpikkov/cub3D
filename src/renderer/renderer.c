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
	line->height= floor(W_HEIGHT / ray->distance);
	line->start = (-line->height / 2) + (W_HEIGHT / 2);
	if (line->start < 0)
		line->start = 0;
	line->end = (line->height / 2) + (W_HEIGHT / 2);
	if (line->end >= W_HEIGHT)
		line->end = W_HEIGHT - 1;
	line->delta = fabs(line->end - line->start);
	if (line->delta == 0)
		line->delta++;
	line->current = line->start;
}

static void	draw_wall(t_ray *ray, t_level *lvl, int x)
{
	t_line		line;
	int			scaled;
	uint32_t	color;

	ft_memset(&line, 0, sizeof(t_line));
	line_init(&line, ray);
	color = 0;
	while (line.current <= line.end)
	{
		scaled = (int)floor(((line.current - line.start) * TILE) / line.delta);
		color = nearest_neighbor(lvl->textures.north, (int)ray->hit_column, scaled);
		mlx_put_pixel(lvl->imgs.fg, x, (int)floor(line.current), color);
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
		// Reset ray struct
		ft_memset(&ray, 0, sizeof(t_ray));
		// Cast ray for each degree within FOV
		if (raycast(&ray, lvl, p, x))
			draw_wall(&ray, lvl, x);
		x++;
	}
}

/**
 * @brief The main function which gets called when rendering a new frame
 */
void	render_surfaces(t_level *lvl, t_player *p)
{
	new_images(lvl);
	level_setup(lvl, p);
	draw_foreground(lvl, p);
}
