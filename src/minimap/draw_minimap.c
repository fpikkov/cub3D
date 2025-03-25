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
//and writes a color according to the tile type(walls one color, floor the other).
//Currently also draws the player as a green square, this is subject to change
//when proper draw_player function is added.
//TODO: Create a designated function for drawing the player.
//TODO: Get rid of debugging utilities.
void	draw_minimap(t_minimap *map)
{
	int		y;
	int		x;
	int		map_y;
	int		map_x;

	y = 0;
	while (y < 256)
		{
			x = 0;
			while (x < 256)
			{
				map_y = map->start_y + (y / map->tile_size);
				map_x = map->start_x + (x / map->tile_size);
				if (map_y >= 0 && map_y < map->height && map_x >= 0 && map_x < map->width)
				{
					if (map->map[map_y][map_x] == 'N')
						mlx_put_pixel(map->img, x, y, 0x39FF14FF);
					else if (map->map[map_y][map_x] == '1')
						mlx_put_pixel(map->img, x, y, 0x00008B30);
					else
						mlx_put_pixel(map->img, x, y, 0xDC143CFF);
				}
				else //this is an else condition to draw white pixels when debugging
					//remove when finished with miniamp development.
				{
					mlx_put_pixel(map->img, x, y, 0x00000FF);
				}
				x++;
			}
			y++;
		}
}
