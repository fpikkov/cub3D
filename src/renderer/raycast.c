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
	r->map_x = (int)p->y;
	r->map_y = (int)p->y;
	r->plane_x = -sin(p->angle) * FOV_RAD;
	r->plane_y = cos(p->angle) * FOV_RAD;
	r->dir_x = cos(p->angle) + r->plane_x * r->camera_x;
	r->dir_y = sin(p->angle) + r->plane_y * r->camera_x;
	r->step_x = 1;
	if (r->dir_x < 0)
		r->step_x = -1;
	r->step_y = 1;
	if (r->dir_y < 0)
		r->step_y = -1;
	r->delta_dist_x = INFINITY;
	if (r->dir_x != 0)
		r->delta_dist_x = fabs(1 / r->dir_x);
	r->delta_dist_y = INFINITY;
	if (r->dir_y != 0)
		r->delta_dist_y = fabs(1 / r->dir_y);
	r->side_dist_x = (r->map_x + 1.0 - p->x) * r->delta_dist_x;
	if (r->dir_x < 0)
		r->side_dist_x = (p->x - r->map_x) * r->delta_dist_x;
	r->side_dist_y = (r->map_y + 1.0 - p->y) * r->delta_dist_y;
	if (r->dir_y < 0)
		r->side_dist_y = (p->y - r->map_y) * r->delta_dist_y;
}

/**
 * @brief Checks if the given co-ordinates reached a wall or out of bounds
 */
bool	is_wall(t_level	*lvl, int x, int y)
{
	if (y <= 0 || x <= 0 || y >= lvl->row_len || x >= lvl->col_len)
	{
		if (DEBUG == 2)
			printf("Out of bounds hit at x:%i y:%i\n", x, y);
		return (true);
	}
	if (lvl->map[y][x] == '1')
	{
		if (DEBUG == 2)
			printf("Wall was hit at x:%i y:%i\n", x, y);
		return (true);
	}
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
			r->map_x += r->step_x;
			r->side = VERTICAL;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = HORIZONTAL;
		}
		if (is_wall(lvl, r->map_x, r->map_y))
			hit = true;
		depth++;
	}
	return (hit);
}

/**
 * TODO: Since the unit circle is flipped,
 * check that the wall textures are correct
 *
 * @brief Checks where on the wall the ray hit and selects a texture.
 */
static void	ray_texture_position(t_ray *ray, t_player *p)
{
	double	wall_pos;

	wall_pos = 0.0;
	if (ray->side == VERTICAL)
		wall_pos = p->y + ray->distance * ray->dir_y;
	else
		wall_pos = p->x + ray->distance * ray->dir_x;
	wall_pos -= floor(wall_pos);
	ray->hit_column = (int)(wall_pos * (double)TILE);
	if (ray->side == VERTICAL && ray->dir_x > 0)
		ray->hit_column = TILE - ray->hit_column - 1;
	if (ray->side == HORIZONTAL && ray->dir_y < 0)
		ray->hit_column = TILE - ray->hit_column - 1;
	if (ray->side == VERTICAL && ray->dir_x > 0)
		ray->wall_type = EAST;
	if (ray->side == VERTICAL && ray->dir_x <= 0)
		ray->wall_type = WEST;
	if (ray->side == HORIZONTAL && ray->dir_y < 0)
		ray->wall_type = SOUTH;
	if (ray->side == HORIZONTAL && ray->dir_y >= 0)
		ray->wall_type = NORTH;
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
	ray->camera_x = (2 * x) / (double)W_WIDTH - 1;
	ray_init(ray, p);
	if (hitscan(ray, lvl))
	{
		if (ray->side == VERTICAL)
			ray->distance = fabs(ray->side_dist_x - ray->delta_dist_x);
		else
			ray->distance = fabs(ray->side_dist_y - ray->delta_dist_y);
		ray_texture_position(ray, p);
		return (true);
	}
	return (false);
}
