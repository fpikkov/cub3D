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
