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

static	t_bresenham	init_line(int start_x, int start_y, int targ_x, int targ_y)
{
	t_bresenham	line;

	ft_memset(&line, 0, sizeof(t_bresenham));
	line.start_x = start_x;
	line.start_y = start_y;
	line.target_x = targ_x;
	line.target_y = targ_y;
	line.delta_x = abs(targ_x - start_x);
	line.delta_y = abs(targ_y - start_y);
	line.err = line.delta_x - line.delta_y;
	if (start_x < targ_x)
		line.step_x = 1;
	else
		line.step_x = -1;
	if (start_y < targ_y)
		line.step_y = 1;
	else
		line.step_y = -1;
	return (line);
}

static void	draw_line(t_minimap *map, t_bresenham line)
{
	while (1)
	{
		mlx_put_pixel(map->img, line.start_x, line.start_y, PLAYER_COLOR);
		if (line.start_x == line.target_x && line.start_y == line.target_y)
			break ;
		line.err2 = 2 * line.err;
		if (line.err2 > -line.delta_y)
		{
			line.err -= line.delta_y;
			line.start_x += line.step_x;
		}
		if (line.err2 < line.delta_x)
		{
			line.err += line.delta_x;
			line.start_y += line.step_y;
		}
	}
}

static	t_arrow	init_arrow(t_minimap *map)
{
	t_arrow	arr;

	ft_memset(&arr, 0, sizeof(t_arrow));
	arr.center_x = (map->player_x - map->start_x) * map->tile_size;
	arr.center_y = (map->player_y - map->start_y) * map->tile_size;
	arr.tip_x = arr.center_x + cos(map->player_angle) * 8;
	arr.tip_y = arr.center_y + sin(map->player_angle) * 8;
	arr.back_x = arr.center_x - cos(map->player_angle) * 4;
	arr.back_y = arr.center_y - sin(map->player_angle) * 4;
	arr.left_x = arr.back_x + cos(map->player_angle + PI / 4) * -8;
	arr.left_y = arr.back_y + sin(map->player_angle + PI / 4) * -8;
	arr.right_x = arr.back_x + cos(map->player_angle - PI / 4) * -8;
	arr.right_y = arr.back_y + sin(map->player_angle - PI / 4) * -8;
	return (arr);
}

static	void	draw_player(t_minimap *map)
{
	t_arrow		arr;
	t_bresenham	line;

	arr = init_arrow(map);
	line = init_line(arr.tip_x, arr.tip_y, arr.left_x, arr.left_y);
	draw_line(map, line);
	line = init_line(arr.left_x, arr.left_y, arr.back_x, arr.back_y);
	draw_line(map, line);
	line = init_line(arr.back_x, arr.back_y, arr.right_x, arr.right_y);
	draw_line(map, line);
	line = init_line(arr.right_x, arr.right_y, arr.tip_x, arr.tip_y);
	draw_line(map, line);
}

void	draw_minimap(t_minimap *map)
{
	int			map_y;
	int			map_x;
	int			pix_y;
	int			pix_x;

	pix_y = -1;
	while (++pix_y < 256)
	{
		pix_x = -1;
		while (++pix_x < 256)
		{
			map_y = map->start_y + (pix_y / map->tile_size);
			map_x = map->start_x + (pix_x / map->tile_size);
			if (map_y >= 0 && map_y < map->height
				&& map_x >= 0 && map_x < map->width)
			{
				if (map->map[map_y][map_x] == '1')
					mlx_put_pixel(map->img, pix_x, pix_y, WALL_COLOR);
				else
					mlx_put_pixel(map->img, pix_x, pix_y, FLOOR_COLOR);
			}
		}
	}
	draw_player(map);
}
