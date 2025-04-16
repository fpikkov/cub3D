/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_door_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:06:00 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/16 15:06:06 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	float	calc_door_pos(t_door_data *door, t_ray *r, t_player *p)
{
	float	door_pos;

	door_pos = 0.0;
	if (r->side == VERTICAL)
		door_pos = p->y + door->dist * r->dir_y;
	else
		door_pos = p->x + door->dist * r->dir_x;
	door_pos -= floorf(door_pos);
	return (door_pos);
}

void	save_door_data(t_ray *r, t_player *p)
{
	float		door_pos;
	t_door_data	*door;

	if (r->door_count >= 20)
		return ;
	door = &r->doors[r->door_count];
	if (r->side == VERTICAL)
		door->dist = fabsf(r->side_dist_x - r->delta_dist_x);
	else
		door->dist = fabsf(r->side_dist_y - r->delta_dist_y);
	door->x = r->map_x;
	door->y = r->map_y;
	door_pos = calc_door_pos(door, r, p);
	door->hit_column = (int)(door_pos * (float)TILE);
	r->door_count++;
}
