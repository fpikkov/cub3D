/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:13:43 by ahentton          #+#    #+#             */
/*   Updated: 2025/03/12 13:13:44 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cube.h"

char	*map[14] = {
	"1111111111111111111111111",
        "1000000000110000000000001",
        "1011000001110000000000001",
        "1001000000000000000000001",
"111111111011000001110000000000001",
"100000000011000001110111111111111",
"11110111111111011100000010001",
"11110111111111011101010010001",
"11000000110101011100000010001",
"10000000000000001100000010001",
"10000000000000001101010010001",
"1100N00111010101111101111000111",
"11110111 1110101   101111010001",
"11111111 1111111   111111111111"
};

//static	bool	init_textures(t_minimap *minimap)

static	void	draw_minimap(mlx_t *mlx, char **map)
{
	mlx_image_t	*minimap = mlx_new_image(mlx, 256, 256);
	if (!minimap)
		return ;
	uint32_t	wall_color = 0xFF0000FF;
	uint32_t	base_color = 0x000000FF;
	uint32_t	player_color = 0x00FF00FF;

	int	map_width = 14;
	int	map_height = 14;
	int	player_x = -1;
	int	player_y = -1;

	for (int y = 0; y < map_height; y++)
	{
		for (int x = 0; x < map_width; x++)
		{
			if (map[y][x] == 'N')
			{
				player_x = x;
				player_y = y;
				break ;
			}
		}
	}
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			int	map_x = (x * map_width) / 256;
			int	map_y = (y * map_height) / 256;

			if (map[map_y][map_x] == '1')
				mlx_put_pixel(minimap, x, y, wall_color);
			else
				mlx_put_pixel(minimap, x, y, base_color);
		}
	}
	if (player_x != -1 && player_y != -1)
	{
		int px = (player_x * 256) / map_width;
		int py = (player_y * 256) / map_height;
		for (int dy = -2; dy <= 2; dy++)
		{
			for (int dx = -2; dx <= 2; dx++)
			{
				int	dot_x = px + dx;
				int	dot_y = py + dy;
				if (dot_x >= 0 && dot_x < 256 && dot_y >= 0 && dot_y < 256)
					mlx_put_pixel(minimap, dot_x, dot_y, player_color);
			}
		}
	}
	mlx_image_to_window(mlx, minimap, 10, 10);
}

int	main(void)
{
	mlx_t	*mlx = mlx_init(W_WIDTH, W_HEIGHT, TITLE, false);
	if (!mlx)
		return (1);

	draw_minimap(mlx, map);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
