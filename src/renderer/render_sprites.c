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

static	uint32_t	pick_color(t_sprite_data *s, t_level *lvl, float x, int y)
{
	uint32_t		color;

	color = 0x0;
	if (lvl->map[(int)s->y][(int)s->x] == 'M')
		color = sprite_interpolation(lvl->textures.monster, x, y);
	return (color);
}

static	void	draw_sprite(t_sprite_data *s, t_level *lvl, int x, float *z_buf)
{
	t_line		line;
	int			scaled_y;
	uint32_t	color;
	float		relative_x;

	relative_x = (float)(x - (s->screen_x - s->width / 2)) / s->width;
	color = 0;
	ft_memset(&line, 0, sizeof(t_line));
	line_init(&line, s->transform_y);
	if (line.current < 0)
		line.current = 0;
	while (line.current <= line.end && line.current < W_HEIGHT)
	{
		if (s->transform_y > 0 && s->transform_y < z_buf[x])
		{
			scaled_y = scale_texture_height(&line);
			color = pick_color(s, lvl, relative_x, scaled_y);
			if (color)
			{
				mlx_put_pixel(lvl->imgs.fg, x, (int)line.current, color);
				draw_light(lvl, &line, x, s->dist);
			}
		}
		line.current++;
	}
}

void	draw_full_sprite(t_sprite_data *s, t_level *lvl, float *z_buffer)
{
	int		start_x;
	int		end_x;
	int		x;

	start_x = s->screen_x - s->width / 2;
	end_x = s->screen_x + s->width / 2;
	if (start_x < 0)
		start_x = 0;
	if (end_x >= W_WIDTH)
		end_x = W_WIDTH - 1;
	x = start_x;
	while (x < end_x)
	{
		draw_sprite(s, lvl, x, z_buffer);
		x++;
	}
}
