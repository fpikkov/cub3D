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
 * @brief Sets up the initial ray vectors.
 *
 * Dirs: Ray direction vectoors converted from radian angle.
 * Map: Initial map position of the ray.
 * Plane: 2D vectors perpendicular to the ray. FOV gives us the scaling factor.
 * Steps: Should we increment or decrement map position.
 * Deltas: The distance between adjacent vertical or horizontal cell borders.
 * Sides: The length of the ray's adjacent and opposite vectors.
 */
static void	ray_init(t_ray *r, t_player *p)
{
	r->map_x = (int)p->x;
	r->map_y = (int)p->y;
	r->plane_x = -sinf(p->angle) * to_radian(FOV);
	r->plane_y = cosf(p->angle) * to_radian(FOV);
	r->dir_x = cosf(p->angle) + r->plane_x * r->camera_x;
	r->dir_y = sinf(p->angle) + r->plane_y * r->camera_x;
	r->step_x = 1;
	if (r->dir_x < 0)
		r->step_x = -1;
	r->step_y = 1;
	if (r->dir_y < 0)
		r->step_y = -1;
	r->delta_dist_x = INFINITY;
	if (r->dir_x != 0)
		r->delta_dist_x = fabsf(1 / r->dir_x);
	r->delta_dist_y = INFINITY;
	if (r->dir_y != 0)
		r->delta_dist_y = fabsf(1 / r->dir_y);
	r->side_dist_x = (r->map_x + 1.0 - p->x) * r->delta_dist_x;
	if (r->dir_x < 0)
		r->side_dist_x = (p->x - r->map_x) * r->delta_dist_x;
	r->side_dist_y = (r->map_y + 1.0 - p->y) * r->delta_dist_y;
	if (r->dir_y < 0)
		r->side_dist_y = (p->y - r->map_y) * r->delta_dist_y;
}

/**
 * @brief Increases the ray's distance until the ray hits a wall
 */
static bool	hitscan(t_ray *r, t_level *lvl, t_player *p)
{
	bool	hit;
	int		depth;

	hit = false;
	depth = -1;
	while (!hit && ++depth < DOF)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = VERTICAL;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = HORIZONTAL;
		}
		if (get_door_type(lvl, r->map_x, r->map_y))
			save_door_data(r, p);
		if (is_wall(lvl, r->map_x, r->map_y))
			hit = true;
	}
	return (hit);
}

/**
 * @brief Checks where on the wall the ray hit and selects a texture.
 */
static void	ray_texture_position(t_ray *ray, t_player *p)
{
	float	wall_pos;

	wall_pos = 0.0;
	if (ray->side == VERTICAL)
		wall_pos = p->y + ray->distance * ray->dir_y;
	else
		wall_pos = p->x + ray->distance * ray->dir_x;
	wall_pos -= floorf(wall_pos);
	ray->hit_column = (int)(wall_pos * (float)TILE);
	if (ray->side == VERTICAL && ray->dir_x < 0)
		ray->hit_column = TILE - ray->hit_column - 1;
	if (ray->side == HORIZONTAL && ray->dir_y > 0)
		ray->hit_column = TILE - ray->hit_column - 1;
	if (ray->side == VERTICAL && ray->dir_x > 0)
		ray->wall_type = EAST;
	if (ray->side == VERTICAL && ray->dir_x <= 0)
		ray->wall_type = WEST;
	if (ray->side == HORIZONTAL && ray->dir_y < 0)
		ray->wall_type = NORTH;
	if (ray->side == HORIZONTAL && ray->dir_y >= 0)
		ray->wall_type = SOUTH;
}

/**
 * NOTE: The raycaster is using Digital Differential Analysis
 *
 * @brief Instantiates a ray from the player position towards the given angle
 * @param[in] ray the ray struct which gets used for distance calculation
 * @param[in] lvl level where the map data gets fetched from
 * @param[in] p player data where we fetch the player's position
 * @param[in] x the x-axis to check oon the camera plane
 * @return true if ray hit a wall, otherwise false
 */
bool	raycast(t_ray *ray, t_level *lvl, t_player *p, int x)
{
	ray->camera_x = (2 * x) / (float)W_WIDTH - 1;
	ray_init(ray, p);
	if (hitscan(ray, lvl, p))
	{
		if (ray->side == VERTICAL)
			ray->distance = fabsf(ray->side_dist_x - ray->delta_dist_x);
		else
			ray->distance = fabsf(ray->side_dist_y - ray->delta_dist_y);
		ray_texture_position(ray, p);
		return (true);
	}
	else
	{
		if (ray->side == VERTICAL)
			ray->distance = fabsf(ray->side_dist_x - ray->delta_dist_x);
		else
			ray->distance = fabsf(ray->side_dist_y - ray->delta_dist_y);
	}
	return (false);
}
