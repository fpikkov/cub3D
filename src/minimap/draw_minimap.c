/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:31:50 by ahentton          #+#    #+#             */
/*   Updated: 2025/03/24 14:31:59 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//draw_minimap draws the minimap, pixel by pixel.
//It loops through every single pixel in the image,
//uses conversion math to track the correct tiles in the **map,
//and writes a color according to the tile content.
//Currently also draws the player as a green square, this is subject to change
//when proper draw_player function is added.

static	void	init_line(t_bresenham *line, t_pixels *pix)
{
	ft_memset(line, 0, sizeof(t_bresenham));
	line->delta_x = abs(pix->tip_x - pix->player_x);
	line->delta_y = abs(pix->tip_y - pix->player_y);
	if (pix->player_x < pix->tip_x)
		line->step_x = 1;
	else
		line->step_x = -1;
	if (pix->player_y < pix->tip_y)
		line->step_y = 1;
	else
		line->step_y = -1;
	line->err = line->delta_x - line->delta_y;
}

static void	draw_line(t_minimap *map, t_pixels *pix, int color)
{
	t_bresenham	line;

	init_line(&line, pix);
	while (1)
	{
		mlx_put_pixel(map->img, pix->player_x, pix->player_y, color);
		if (pix->player_x == pix->tip_x && pix->player_y == pix->tip_y)
			break ;
		line.err2 = 2 * line.err;
		if (line.err2 > -line.delta_y)
		{
			line.err -= line.delta_y;
			pix->player_x += line.step_x;
		}
		if (line.err2 < line.delta_x)
		{
			line.err += line.delta_x;
			pix->player_y += line.step_y;
		}
	}
}

static	void	draw_player(t_minimap *map, t_pixels *pix)
{
	pix->player_x = (map->player_x - map->start_x) * map->tile_size;
	pix->player_y = (map->player_y - map->start_y) * map->tile_size;
	pix->y = 0;
	while (pix->y <= 2)
	{
		pix->x = 0;
		while (pix->x <= 2)
		{
			mlx_put_pixel(map->img, pix->player_x + pix->x, pix->player_y + pix->y, PLAYER_COLOR);
			pix->x++;
		}
		pix->y++;
	}
	pix->tip_x = pix->player_x + cos(map->player_angle) * 6;
	pix->tip_y = pix->player_y + sin(map->player_angle) * 6;
	draw_line(map, pix, PLAYER_COLOR);
}

void	draw_minimap(t_minimap *map)
{
	t_pixels	pix;
	int			map_y;
	int			map_x;

	ft_memset(&pix, 0, sizeof(t_pixels));
	while (pix.y < 256)
	{
		pix.x = 0;
		while (pix.x < 256)
		{
			map_y = map->start_y + (pix.y / map->tile_size);
			map_x = map->start_x + (pix.x / map->tile_size);
			if (map_y >= 0 && map_y < map->height && map_x >= 0 && map_x < map->width)
			{
				if (map->map[map_y][map_x] == '1')
					mlx_put_pixel(map->img, pix.x, pix.y, WALL_COLOR);
				else
					mlx_put_pixel(map->img, pix.x, pix.y, FLOOR_COLOR);
			}
			pix.x++;
		}
		pix.y++;
	}
	draw_player(map, &pix);
}
