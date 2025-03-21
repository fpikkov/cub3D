/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:24:26 by ahentton          #+#    #+#             */
/*   Updated: 2025/03/20 13:24:33 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

#define RANGE 5
#define MAP_HEIGHT 14
#define MAP_WIDTH 33

char	*map[14] = {
"111111111111111111111111111111111",
"1N0000000000000000110000000000001",
"111111111011000001110000000000001",
"110011111001000000000000000000001",
"111111111011000001110000000000001",
"110000000011000001110111111111111",
"111101111111110111000000100011111",
"111101111111110111010100100011111",
"110000001101010111000000100011111",
"100000000000000111000000100011111",
"100000000000000011010100100011111",
"110000011101010111110111100011111",
"111101111111010111110111101000111",
"111111111111111111111111111111111"
};

static	void	draw_minimap(mlx_t *mlx, char **map, int player_x, int player_y)
{
	mlx_image_t	*minimap;
	int		y;
	int		x;
	int		map_x;
	int		map_y;
	int		start_x;
	int		start_y;
	float		tile_size;

	minimap = mlx_new_image(mlx, 256, 256);
	if (!minimap)
		return ;

	tile_size = 256.0 / (RANGE * 2 + 1);
	start_x = player_x - RANGE;
	start_y = player_y - RANGE;
	if (MAP_WIDTH - player_x < 5)
		start_x = player_x - (RANGE * 2 - (MAP_WIDTH - player_x - 1));
	if (MAP_HEIGHT - player_y < 5)
		start_y = player_y - (RANGE * 2 - (MAP_HEIGHT - player_y - 1));
	if (player_x - RANGE < 0)
		start_x = RANGE + (player_x - RANGE - 1);
	if (player_y - RANGE < 0)
		start_y = RANGE + (player_x - RANGE - 1);
	y = 0;
	while (y < 256)
	{
		x = 0;
		while (x < 256)
		{
			map_y = start_y + (y / tile_size);
			map_x = start_x + (x / tile_size);
			if (map_y >= 0 && map_y < MAP_HEIGHT && map_x >= 0 && map_x < MAP_WIDTH)
			{
				if (map[map_y][map_x] == 'N')
					mlx_put_pixel(minimap, x, y, 0x39FF14FF);
				else if (map[map_y][map_x] == '1')
					mlx_put_pixel(minimap, x, y, 0x00008B30);
				else
					mlx_put_pixel(minimap, x, y, 0xDC143CFF);
			}
			else
			{
				mlx_put_pixel(minimap, x, y, 0x00000FF);
			}
			x++;
		}
		y++;
	}
	mlx_image_to_window(mlx, minimap, 10, 10);
	//draw_player_arrow(minimap);
}

int	main(void)
{
	mlx_t	*mlx = mlx_init(W_WIDTH, W_HEIGHT, TITLE, false);
	if (!mlx)
		return (1);

	draw_minimap(mlx, map, 1, 1);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
/*
static	void	draw_player_arrow(mlx_image_t *minimap)
{
	int	tile_size;
	int	center_x;
	int	center_y;
	int	x;
	int	y;

	tile_size = 256 / (RANGE * 2 + 1);
	center_x = 128;
	center_y = 128;
	mlx_put_pixel(minimap, center_x, center_y - tile_size / 2, 0x39FF14FF);

	y = 1;
	while (y < tile_size / 2)
	{
		x = -y;
		while (x <= y)
		{
			mlx_put_pixel(minimap, center_x + x, center_y - tile_size / 2 + y, 0x39FF14FF);
			x++;
		}
		y++;
	}
}*/

