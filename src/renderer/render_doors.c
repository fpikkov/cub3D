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
void	save_door_data(t_ray *r, t_player *p)
{
	float		door_pos;
	t_door_data	*door;

	if (r->door_count >= 10)
		return ;
	door = &r->doors[r->door_count];
	if (r->side == VERTICAL)
		door->door_dist = fabsf(r->side_dist_x - r->delta_dist_x);
	else
		door->door_dist = fabsf(r->side_dist_y - r->delta_dist_y);
	door->door_x = r->map_x;
	door->door_y = r->map_y;
	door_pos = calc_door_pos(door, r, p);
	door->door_column = (int)(door_pos * (float)TILE);
	if (r->side == VERTICAL && r->dir_x < 0)
		r->doors->door_column = TILE - r->doors->door_column - 1;
	if (r->side == HORIZONTAL && r->dir_y > 0)
		r->doors->door_column = TILE - r->doors->door_column - 1;
	r->door_count++;
}

uint32_t	pick_door_texture(t_door_data *door, t_level *lvl, int y)
{
	uint32_t	color;

	color = 0x0;
	if (lvl->map[door->door_y][door->door_x] == '2')
		color = nearest_neighbor(lvl->textures.door1, (int)door->door_column, y);
	else if (lvl->map[door->door_y][door->door_x] == '3')
		color = nearest_neighbor(lvl->textures.door2, (int)door->door_column, y);
	else if (lvl->map[door->door_y][door->door_x] == '4')
		color = nearest_neighbor(lvl->textures.door3, (int)door->door_column, y);
	else if (lvl->map[door->door_y][door->door_x] == '5')
		color = nearest_neighbor(lvl->textures.door4, (int)door->door_column, y);
	else if (lvl->map[door->door_y][door->door_x] == '6')
		color = nearest_neighbor(lvl->textures.door5, (int)door->door_column, y);
	else if (lvl->map[door->door_y][door->door_x] == '7')
		color = nearest_neighbor(lvl->textures.door6, (int)door->door_column, y);
	else if (lvl->map[door->door_y][door->door_x] == '8')
		color = nearest_neighbor(lvl->textures.door7, (int)door->door_column, y);
	return (color);
}

void	draw_doors(t_ray *ray, t_level *lvl, int x)
{
	t_line	line;
	int		scaled_y;
	uint32_t	color;

	color = 0;
	while (--ray->door_count >= 0)
	{
		ft_memset(&line, 0, sizeof(t_line));
		line_init(&line, ray->doors[ray->door_count].door_dist);
		while (line.current <= line.end)
		{
			if (line.current >= 0 && line.current < W_HEIGHT)
			{
				scaled_y = (int)floor(((line.current - line.start) \
				 * (TILE - 1)) / line.delta);
				color = pick_door_texture(&ray->doors[ray->door_count], lvl, scaled_y);
				if (color)
					mlx_put_pixel(lvl->imgs.fg, x, (int)line.current, color);
			}
			line.current++;
		}
	}
}
