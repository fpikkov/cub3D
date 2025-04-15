/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:55:14 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/07 15:55:16 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	line_init(t_line *line, float distance)
{
	line->height = W_HEIGHT / distance;
	line->start = (-line->height / 2) + (W_HEIGHT / 2);
	line->end = (line->height / 2) + (W_HEIGHT / 2);
	line->delta = line->end - line->start;
	if (line->delta == 0)
		line->delta++;
	line->current = line->start;
}

static uint32_t	select_texture(t_ray *ray, t_level *lvl, int y)
{
	uint32_t	color;

	color = 0x0;
	if (ray->wall_type == NORTH)
		color = nearest_neighbor(lvl->textures.north, (int)ray->hit_column, y);
	else if (ray->wall_type == EAST)
		color = nearest_neighbor(lvl->textures.east, (int)ray->hit_column, y);
	else if (ray->wall_type == SOUTH)
		color = nearest_neighbor(lvl->textures.south, (int)ray->hit_column, y);
	else if (ray->wall_type == WEST)
		color = nearest_neighbor(lvl->textures.west, (int)ray->hit_column, y);
	return (color);
}

/**
 * @brief Draws vertical line onto the screen x position based on how far
 * the ray hit the wall on the map. The image size gets interpolated so pixel
 * data is always fetched from a square range defined by the TILE constant.
 * @param[in] ray the casted ray struct
 * @param[in] lvl the current level
 * @param[in] x the horizontal screen coordinate
 */
static void	draw_line(t_ray *ray, t_level *lvl, int x)
{
	t_line		line;
	int			scaled_y;
	uint32_t	color;

	ft_memset(&line, 0, sizeof(t_line));
	line_init(&line, ray->distance);
	color = 0;
	while (line.current <= line.end && line.current < W_HEIGHT)
	{
		if (line.current < 0)
			line.current = 0;
		scaled_y = scale_texture_height(&line);
		color = select_texture(ray, lvl, scaled_y);
		mlx_put_pixel(lvl->imgs.fg, x, line.current, color);
		draw_light(lvl, &line, x, ray->distance);
		line.current++;
	}
	light_floor(lvl, &line, x);
}

static	bool	check_unique(t_sprite_data sprites[20], int sprite_count, t_sprite_data *hit_sprite)
{
	int		i;

	i = 0;
	while (i < sprite_count)
	{
		if ((int)sprites[i].x == (int)hit_sprite->x && (int)sprites[i].y == (int)hit_sprite->y)
			return (false);
		i++;
	}
	return (true);
}
/**
 * @brief Draws walls line by line to the foreground image
 */
static void	draw_foreground(t_level *lvl, t_player *p)
{
	t_ray	ray;
	t_sprite_data	sprites[20];
	int		sprite_count;
	int		x;
	int		i;

	ft_memset(&sprites, 0, sizeof(t_sprite_data) * 20);
	sprite_count = 0;
	x = 0;
	while (x < W_WIDTH)
	{
		i = 0;
		ft_memset(&ray, 0, sizeof(t_ray));
		if (raycast(&ray, lvl, p, x))
			draw_line(&ray, lvl, x);
		else
			draw_fog(&ray, lvl, x);
		if (ray.door_count > 0)
			draw_doors(&ray, lvl, x);
		while (i < ray.sprite_count && sprite_count < 20)
		{
			if (check_unique(sprites, sprite_count, ray.sprites) == true)
			{
				sprites[sprite_count] = ray.sprites[i];
				sprite_count++;
			}
			i++;
		}
		x++;
	}
	if (sprite_count > 0)
		draw_all_sprites(sprites, sprite_count, lvl);
}

/**
 * @brief The main function which gets called when rendering a new frame
 */
void	render_surfaces(t_level *lvl, t_player *p)
{
	level_setup(lvl, p);
	reset_foreground(lvl);
	draw_foreground(lvl, p);
}
