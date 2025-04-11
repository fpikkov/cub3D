/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:35:03 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/02 13:35:09 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	save_sprite_data(t_ray *r, t_player *p)
{
	float				sprite_pos;
	t_sprite_data		*sprite;

	if (r->sprite_count >= 20)
		return ;
	sprite = &r->sprites[r->sprite_count];
	if (r->side == VERTICAL)
		sprite->dist = fabsf(r->side_dist_x - r->delta_dist_x);
	else
		sprite->dist = fabsf(r->side_dist_y - r->delta_dist_y);
	sprite->x = r->map_x;
	sprite->y = r->map_y;
	sprite_pos = calc_sprite_pos(sprite, r, p);
	sprite->hit_column = (int)(sprite_pos * (float)TILE);
	r->sprite_count++;
}

uint32_t	pick_sprite_texture(t_sprite_data *sprite, t_level *lvl, int y)
{
	uint32_t		color;

	color = 0x0;
	if (lvl->map[sprite->y][sprite->x] == 'M')
		color = nearest_neighbor(lvl->textures.monster, sprite->hit_column, y);
	return (color);
}

void	draw_sprite(t_ray *ray, t_level *lvl, int x)
{
	t_line		line;
	int			scaled_y;
	uint32_t	color;

	color = 0;
	ft_memset(&line, 0, sizeof(t_line));
	line_init(&line, ray->sprites[ray->sprite_count].dist);
	if (line.current < 0)
		line.current = 0;
	while (line.current <= line.end && line.current < W_HEIGHT)
	{
		scaled_y = scale_texture_height(&line);
		color = pick_sprite_texture(&ray->sprites[ray->sprite_count], \
		lvl, scaled_y);
		if (color)
		{
			mlx_put_pixel(lvl->imgs.fg, x, (int)line.current, color);
			draw_light(lvl, &line, x, \
			ray->sprites[ray->sprite_count].dist);
		}
		line.current++;
	}
	ray->sprite_count--;
}
