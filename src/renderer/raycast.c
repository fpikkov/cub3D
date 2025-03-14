/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:52:55 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/14 15:52:56 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Sets up variables before starting the ray casting loop
 */
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

/**
 * @brief Checks if the given co-ordinates reached a wall or out of bounds
 */
static bool	is_wall(t_level	*lvl, int x, int y)
{
	if (y <= 0 || x <= 0 || y >= lvl->row_len || x >= lvl->col_len)
		return (true);
	if (lvl->map[y][x] == '1')
		return (true);
	return (false);
}

/**
 * @brief Increases the ray's distance until the ray hits a wall
 */
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

/**
 * NOTE: The current raycasting implementation uses Bresenham's line algorithm
 *
 * @brief Instantiates a ray from the player position towards the given angle
 * @param[in] lvl level where the map data gets fetched from
 * @param[in] p player data where we fetch the player's position
 * @param[in] angle the starting direction of the ray
 * @return distance to the reached wall from player position, 0.0 if unreached
 */
double	raycast(t_level *lvl, t_player *p, double angle)
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
