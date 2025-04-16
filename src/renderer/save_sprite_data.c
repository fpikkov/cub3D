/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_sprite_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:04:19 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/16 15:04:23 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	bool	check_unique(t_ray *ray)
{
	int		i;

	i = 0;
	while (i < ray->sprite_count)
	{
		if ((int)ray->sprites[i].x == ray->map_x \
		&& (int)ray->sprites[i].y == ray->map_y)
			return (false);
		i++;
	}
	return (true);
}

void	save_sprite_data(t_ray *r, t_player *p)
{
	t_sprite_data		*s;
	float				rel_x;
	float				rel_y;
	float				inv_det;

	if (r->sprite_count >= 20 || !check_unique(r))
		return ;
	s = &r->sprites[r->sprite_count];
	s->x = r->map_x + 0.5f;
	s->y = r->map_y + 0.5f;
	rel_x = s->x - p->x;
	rel_y = s->y - p->y;
	s->dist = rel_x * rel_x + rel_y * rel_y;
	inv_det = 1.0f / (r->plane_x * r->dir_y - r->dir_x * r->plane_y);
	s->transform_x = inv_det * (p->dir_y * rel_x - p->dir_x * rel_y);
	s->transform_y = inv_det * (-r->plane_y * rel_x + r->plane_x * rel_y);
	if (s->transform_y < 0.1f)
		s->transform_y = 0.1f;
	s->screen_x = (W_WIDTH / 2) * (1 + s->transform_x / s->transform_y);
	s->height = abs((int)(W_HEIGHT / s->transform_y));
	s->width = s->height;
	r->sprite_count++;
}
