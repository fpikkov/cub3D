/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:49:54 by fpikkov           #+#    #+#             */
/*   Updated: 2025/02/28 12:49:57 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	mlx_t		*mlx;
	mlx_image_t	*img;
	int32_t		*buffer;
	int		x;
	int		y;

	mlx = mlx_init(1920, 1080, "Cub3d", true);
	img = mlx_new_image(mlx, 1920, 1080);
	buffer = (int32_t *)img->pixels;

	for (y = 0; y < 1080; y++)
	{
		for (x = 0; x < 1920; x++)
		{
			if (y < 540)
				buffer[y * 1920 + x] = 0xFFFFA500;
			else
				buffer[y * 1920 + x] = 0xFF505050;
		}
	}
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);

	return (EXIT_SUCCESS);
}
