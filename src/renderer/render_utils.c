/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:42:47 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/02 13:42:52 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

float	calc_door_pos(t_door_data *door, t_ray *r, t_player *p)
{
	float	door_pos;

	door_pos = 0.0;
	if (r->side == VERTICAL)
		door_pos = p->y + door->door_dist * r->dir_y;
	else
		door_pos = p->x + door->door_dist * r->dir_x;
	door_pos -= floorf(door_pos);
	return (door_pos);
}
