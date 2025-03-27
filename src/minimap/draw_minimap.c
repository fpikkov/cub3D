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

#include "constants.h"
#include "cube.h"
#include "libft.h"

//draw_minimap draws the minimap, pixel by pixel.
//It loops through every single pixel in the image,
//uses conversion math to track the correct tiles in the **map,
//and writes a color according to the tile content.
//Currently also draws the player as a green square, this is subject to change
//when proper draw_player function is added.

static	void	init_line(t_bresenham *line, int start_x, int start_y, int target_x, int target_y)
{
	ft_memset(line, 0, sizeof(t_bresenham));
	line->delta_x = abs(target_x - start_x);
	line->delta_y = abs(target_y - start_y);
	line->err = line->delta_x - line->delta_y;
	if (start_x < target_x)
		line->step_x = 1;
	else
		line->step_x = -1;
	if (start_y < target_y)
		line->step_y = 1;
	else
		line->step_y = -1;
}

static void	draw_line(t_minimap *map, int start_x, int start_y, int target_x, int target_y)
{
	t_bresenham	line;

	init_line(&line, start_x, start_y, target_x, target_y);
	while (1)
	{
		mlx_put_pixel(map->img, start_x, start_y, PLAYER_COLOR);
		if (start_x == target_x && start_y == target_y)
			break ;
		line.err2 = 2 * line.err;
		if (line.err2 > -line.delta_y)
		{
			line.err -= line.delta_y;
			start_x += line.step_x;
		}
		if (line.err2 < line.delta_x)
		{
			line.err += line.delta_x;
			start_y += line.step_y;
		}
	}
}

static	void	init_arrow(t_arrow *arr, t_minimap *map)
{
	ft_memset(arr, 0, sizeof(t_arrow));
	arr->center_x = (map->player_x - map->start_x) * map->tile_size;
	arr->center_y = (map->player_y - map->start_y) * map->tile_size;
	arr->tip_x = arr->center_x + cos(map->player_angle) * 8;
	arr->tip_y = arr->center_y + sin(map->player_angle) * 8;
	arr->back_x = arr->center_x - cos(map->player_angle) * 4;
	arr->back_y = arr->center_y - sin(map->player_angle) * 4;
	arr->left_x = arr->back_x + cos(map->player_angle + PI / 4) * -8;
	arr->left_y = arr->back_y + sin(map->player_angle + PI / 4) * -8;
	arr->right_x = arr->back_x + cos(map->player_angle - PI / 4) * -8;
	arr->right_y = arr->back_y + sin(map->player_angle - PI / 4) * -8;
}

static	void	draw_player(t_minimap *map)
{
	t_arrow	arr;

	init_arrow(&arr, map);
	draw_line(map, arr.tip_x, arr.tip_y, arr.left_x, arr.left_y);
	draw_line(map, arr.left_x, arr.left_y, arr.back_x, arr.back_y);
	draw_line(map, arr.back_x, arr.back_y, arr.right_x, arr.right_y);
	draw_line(map, arr.right_x, arr.right_y, arr.tip_x, arr.tip_y);
}

void	draw_minimap(t_minimap *map)
{
	int			map_y;
	int			map_x;
	int			pix_y;
	int			pix_x;

	pix_y = 0;
	while (pix_y < 256)
	{
		pix_x = 0;
		while (pix_x < 256)
		{
			map_y = map->start_y + (pix_y / map->tile_size);
			map_x = map->start_x + (pix_x / map->tile_size);
			if (map_y >= 0 && map_y < map->height && map_x >= 0 && map_x < map->width)
			{
				if (map->map[map_y][map_x] == '1')
					mlx_put_pixel(map->img, pix_x, pix_y, WALL_COLOR);
				else
					mlx_put_pixel(map->img, pix_x, pix_y, FLOOR_COLOR);
			}
			pix_x++;
		}
		pix_y++;
	}
	draw_player(map);
}
