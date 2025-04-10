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

static	mlx_texture_t	*pick_exit_texture(t_level *lvl, int status)
{
	if (status == CLOSED)
		return (lvl->textures.exit1);
	else if (status == OPENING1)
		return (lvl->textures.exit2);
	else if (status == OPENING2)
		return (lvl->textures.exit3);
	else if (status == OPENING3)
		return (lvl->textures.exit4);
	else if (status == OPENING4)
		return (lvl->textures.exit5);
	else if (status == OPENING5)
		return (lvl->textures.exit6);
	else if (status == OPEN)
		return (lvl->textures.exit7);
	return (NULL);

}
/*
mlx_texture_t	*pick_door_texture(t_level *lvl, int status)
{
	if (status == CLOSED)
		return (lvl->textures.door1);
	else if (status == OPENING1)
		return (lvl->textures.door2);
	else if (status == OPENING2)
		return (lvl->textures.door3);
	else if (status == OPENING3)
		return (lvl->textures.door4);
	else if (status == OPENING4)
		return (lvl->textures.door5);
	else if (status == OPENING5)
		return (lvl->textures.door6);
	else if (status == OPEN)
		return (lvl->textures.door7);
	return (NULL);

}*/

uint32_t	pick_sprite_texture(t_sprite_data *sprite, t_level *lvl, int y)
{
	uint32_t	color;
	mlx_texture_t	*tex;

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
	else if (lvl->map[sprite->y][sprite->x] == 'P')
	{
		tex = pick_exit_texture(lvl, lvl->exit.status);
		color = nearest_neighbor(tex, sprite->hit_column, y);
	}
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
