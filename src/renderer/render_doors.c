/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:35:03 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/02 13:35:09 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//TODO: Try to queue up door data from all the doors in the same ray hit on current x-axis,
//	Maybe you can make door.next without it being a pointer, that would be something
//	also make sure the lvl->doored bool is initialized correctly. very important for safety
void	save_door_data(t_ray *r, t_level *lvl, t_player *p)
{
	float	door_pos;

	if (!r->doors)
	{
		if (r->side == VERTICAL)
			r->door_dist = fabsf(r->side_dist_x - r->delta_dist_x);
		else
			r->door_dist = fabsf(r->side_dist_y - r->delta_dist_y);
		r->door_x = r->map_x;
		r->door_y = r->map_y;
		door_pos = calc_door_pos(r, p);
		r->door_column = (int)(door_pos * (float)TILE);
		if (r->side == VERTICAL && r->dir_x < 0)
			r->door_column = TILE - r->door_column - 1;
		if (r->side == HORIZONTAL && r->dir_y > 0)
			r->door_column = TILE - r->door_column - 1;
		if (pick_door_texture(r, lvl, 0))
			r->doors = true;
		else
			r->doors = false;
	}
}

uint32_t	pick_door_texture(t_ray *ray, t_level *lvl, int y)
{
	uint32_t	color;

	color = 0x0;
	if (lvl->map[ray->door_y][ray->door_x] == '2')
		color = nearest_neighbor(lvl->textures.door1, (int)ray->door_column, y);
	else if (lvl->map[ray->door_y][ray->door_x] == '3')
		color = nearest_neighbor(lvl->textures.door2, (int)ray->door_column, y);
	else if (lvl->map[ray->door_y][ray->door_x] == '4')
		color = nearest_neighbor(lvl->textures.door3, (int)ray->door_column, y);
	else if (lvl->map[ray->door_y][ray->door_x] == '5')
		color = nearest_neighbor(lvl->textures.door4, (int)ray->door_column, y);
	else if (lvl->map[ray->door_y][ray->door_x] == '6')
		color = nearest_neighbor(lvl->textures.door5, (int)ray->door_column, y);
	else if (lvl->map[ray->door_y][ray->door_x] == '7')
		color = nearest_neighbor(lvl->textures.door6, (int)ray->door_column, y);
	else if (lvl->map[ray->door_y][ray->door_x] == '8')
		color = nearest_neighbor(lvl->textures.door7, (int)ray->door_column, y);
	return (color);
}

void	draw_door(t_ray *ray, t_level *lvl, int x)
{
	t_line	line;
	int		scaled_y;
	uint32_t	color;

	ft_memset(&line, 0, sizeof(t_line));
	line_init(&line, ray->door_dist);
	color = 0;
	while (line.current <= line.end)
	{
		if (line.current >= 0 && line.current < W_HEIGHT)
		{
			scaled_y = (int)floor(((line.current - line.start) \
			 * (TILE - 1)) / line.delta);
			color = pick_door_texture(ray, lvl, scaled_y);
			if (color)
				mlx_put_pixel(lvl->imgs.fg, x, (int)line.current, color);
		}
		line.current++;
	}
}
