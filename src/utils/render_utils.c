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

float	calc_sprite_pos(t_sprite_data *sprite, t_ray *r, t_player *p)
{
	float	sprite_pos;

	sprite_pos = 0.0;
	if (r->side == VERTICAL)
		sprite_pos = p->y + sprite->dist * r->dir_y;
	else
		sprite_pos = p->x + sprite->dist * r->dir_x;
	sprite_pos -= floorf(sprite_pos);
	return (sprite_pos);
}

float	calc_door_pos(t_door_data *door, t_ray *r, t_player *p)
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
