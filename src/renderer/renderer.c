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
 * @brief Renders the floor and ceiling and initializes player position
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

static void	ray_init(t_ray *r, t_player *p, double angle)
{
	// Ray direction
	r->step_x = cos(angle);
	r->step_y = sin(angle);
	// Map position
	r->map_x = (int)p->y;
	r->map_y = (int)p->y;
	// Step direction (positive or negative)
	r->delta_x = -1;
	if (r->step_x > 0)
		r->delta_x = 1;
	r->delta_y = -1;
	if (r->step_y > 0)
		r->delta_y = 1;
	// Delta distances
	r->delta_dist_x = INFINITY;
	if (r->step_x != 0)
		r->delta_dist_x = fabs(1 / r->step_x);
	r->delta_dist_y = INFINITY;
	if (r->step_y != 0)
		r->delta_dist_y = fabs(1 / r->step_y);
	// Side distances
	r->side_dist_x = (p->x - r->map_x) * r->delta_dist_x;
	if (r->step_x > 0)
		r->side_dist_x = (r->map_x + 1.0 - p->x) * r->delta_dist_x;
	r->side_dist_y = (p->y - r->map_y) * r->delta_dist_y;
	if (r->step_y > 0)
		r->side_dist_y = (r->map_y + 1.0 - p->y) * r->delta_dist_y;
}

// TODO: Square the map and store map width and height
static bool	is_wall(t_level	*lvl, int x, int y)
{
	if (y < 0 || x < 0 || !lvl->map[y] || !lvl->map[y][x])
		return (true);
	if (x > (int)ft_strlen(lvl->map[y]))
		return (true);
	if (lvl->map[y][x] == '1')
		return (true);
	return (false);
}

static bool	hitscan(t_ray *r, t_level *lvl)
{
	bool	hit;
	int		depth;

	hit = false;
	depth = 0;
	while (!hit && depth < DOF)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->delta_x;
			r->side = 0;
		}
		else
		{
			r->delta_dist_y += r->delta_dist_y;
			r->map_y += r->delta_y;
			r->side = 1;
		}
		if (is_wall(lvl, r->map_x, r->map_y))
			hit = true;
		depth++;
	}
	return (hit);
}

static double	raycast(t_level *lvl, t_player *p, double angle)
{
	t_ray	r;
	double	distance;

	distance = 0.0;
	ft_memset(&r, 0, sizeof(t_ray));
	ray_init(&r, p, angle);
	if (hitscan(&r, lvl))
	{
		distance = r.side_dist_y - r.delta_dist_y;
		if (r.side == 0)
			distance = r.side_dist_x - r.delta_dist_x;
		return (fabs(distance));
	}
	return (0.0);
}

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
 * TODO: Implement raycasting features so we know how far to render walls
 */
void	render_surfaces(t_level *lvl, t_player *p)
{
	new_images(lvl);
	level_setup(lvl, p);
	draw_walls(lvl, p);
}
