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
