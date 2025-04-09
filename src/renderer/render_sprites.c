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
	float		sprite_pos;
	t_sprite_data	*sprite;

	if (r->sprite_count >= 30)
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
	uint32_t	color;

	color = 0x0;
	if (lvl->map[sprite->y][sprite->x] == '2')
		color = nearest_neighbor(lvl->textures.door1, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == '3')
		color = nearest_neighbor(lvl->textures.door2, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == '4')
		color = nearest_neighbor(lvl->textures.door3, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == '5')
		color = nearest_neighbor(lvl->textures.door4, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == '6')
		color = nearest_neighbor(lvl->textures.door5, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == '7')
		color = nearest_neighbor(lvl->textures.door6, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == '8')
		color = nearest_neighbor(lvl->textures.door7, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == 'M')
		color = nearest_neighbor(lvl->textures.monster, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == 'R')
		color = nearest_neighbor(lvl->textures.exit1, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == 'T')
		color = nearest_neighbor(lvl->textures.exit2, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == 'Y')
		color = nearest_neighbor(lvl->textures.exit3, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == 'U')
		color = nearest_neighbor(lvl->textures.exit4, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == 'I')
		color = nearest_neighbor(lvl->textures.exit5, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == 'O')
		color = nearest_neighbor(lvl->textures.exit6, sprite->hit_column, y);
	else if (lvl->map[sprite->y][sprite->x] == 'P')
		color = nearest_neighbor(lvl->textures.exit7, sprite->hit_column, y);
	return (color);
}

void	draw_sprites(t_ray *ray, t_level *lvl, int x)
{
	t_line		line;
	int			scaled_y;
	uint32_t	color;

	color = 0;
	while (--ray->sprite_count >= 0)
	{
		ft_memset(&line, 0, sizeof(t_line));
		line_init(&line, ray->sprites[ray->sprite_count].dist);
		while (line.current <= line.end && line.current < W_HEIGHT)
		{
			if (line.current < 0)
				line.current = 0;
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
	}
}
