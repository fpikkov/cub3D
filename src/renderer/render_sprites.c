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

static	uint32_t	sprite_interpolation(mlx_texture_t *tex, float relative_x, uint32_t y)
{
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	color;
	uint8_t		*ptr;

	src_x = (uint32_t)(relative_x * tex->width);
	if (src_x >= tex->width)
		src_x = tex->width - 1;
	src_y = (uint32_t)(((float)y / TILE) * tex->height);
	if (src_y >= tex->height)
		src_y = tex->height - 1;
	ptr = &tex->pixels[(src_y * tex->width + src_x) * tex->bytes_per_pixel];
	color = 0;
	color |= *ptr << 24;
	ptr++;
	color |= *ptr << 16;
	ptr++;
	color |= *ptr << 8;
	ptr++;
	color |= *ptr;
	return (color);
}

void	save_sprite_data(t_ray *r, t_player *p)
{
	t_sprite_data		*sprite;
	float			rel_x;
	float			rel_y;
	float			inv_det;

	if (r->sprite_count >= 20)
		return ;
	sprite = &r->sprites[r->sprite_count];
	sprite->x = r->map_x + 0.5f;
	sprite->y = r->map_y + 0.5f;
	rel_x = sprite->x - p->x;
	rel_y = sprite->y - p->y;
	sprite->dist = rel_x * rel_x + rel_y * rel_y;
	inv_det = 1.0f / (r->plane_x * r->dir_y - r->dir_x * r->plane_y);
	sprite->transform_x = inv_det * (p->dir_y * rel_x - p->dir_x * rel_y);
	sprite->transform_y = inv_det * (-r->plane_y * rel_x + r->plane_x * rel_y);
	if (sprite->transform_y < 0.1f)
		sprite->transform_y = 0.1f;
	sprite->screen_x = (W_WIDTH / 2) * (1 + sprite->transform_x / sprite->transform_y);
	sprite->height = abs((int)(W_HEIGHT / sprite->transform_y));
	sprite->width = sprite->height;
	r->sprite_count++;
}

static	uint32_t	pick_sprite_texture(t_sprite_data *sprite, t_level *lvl, float relative_x, int y)
{
	uint32_t		color;

	color = 0x0;
	if (lvl->map[(int)sprite->y][(int)sprite->x] == 'M')
		color = sprite_interpolation(lvl->textures.monster, relative_x, y);
	return (color);
}

void	draw_sprite(t_sprite_data *sprite, t_level *lvl, int x)
{
	t_line		line;
	int			scaled_y;
	uint32_t	color;
	float	relative_x;

	relative_x = (float)(x - (sprite->screen_x - sprite->width / 2)) / sprite->width;
	color = 0;
	ft_memset(&line, 0, sizeof(t_line));
	line_init(&line, sprite->transform_y);
	if (line.current < 0)
		line.current = 0;
	while (line.current <= line.end && line.current < W_HEIGHT)
	{
		scaled_y = scale_texture_height(&line);
		color = pick_sprite_texture(sprite, lvl, relative_x, scaled_y);
		if (color)
		{
			mlx_put_pixel(lvl->imgs.fg, x, (int)line.current, color);
			draw_light(lvl, &line, x, \
			sprite->dist);
		}
		line.current++;
	}
}

void	draw_full_sprite(t_sprite_data *sprite, t_level *lvl)
{
	int		start_x;
	int		end_x;
	int		x;

	start_x = sprite->screen_x - sprite->width / 2;
	end_x = sprite->screen_x + sprite->width / 2;
	if (start_x < 0)
		start_x = 0;
	if (end_x >= W_WIDTH)
		end_x = W_WIDTH - 1;
	for (x = start_x; x < end_x; x++)
		draw_sprite(sprite, lvl, x);
}

void	draw_all_sprites(t_sprite_data *sprites, int sprite_count, t_level *lvl)
{
	while (--sprite_count >= 0)
		draw_full_sprite(&sprites[sprite_count], lvl);
}
