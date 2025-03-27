/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:33:48 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/27 15:33:49 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	image_fill(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

// TODO: Use draw_circle to create differently shaded rings around the light circle
/* static void	circle_line(mlx_image_t *img ,uint32_t x, uint32_t y, uint32_t col)
{
	uint32_t	center_x;
	uint32_t	center_y;

	center_x = W_WIDTH / 2;
	center_y = W_HEIGHT / 2;
	mlx_put_pixel(img, center_x + x, center_y + y, col);
	mlx_put_pixel(img, center_x + y, center_y + x, col);
	mlx_put_pixel(img, center_x - x, center_y + y, col);
	mlx_put_pixel(img, center_x - y, center_y + x, col);
	mlx_put_pixel(img, center_x + x, center_y - y, col);
	mlx_put_pixel(img, center_x + y, center_y - x, col);
	mlx_put_pixel(img, center_x - x, center_y - y, col);
	mlx_put_pixel(img, center_x - y, center_y - x, col);
}

static void	draw_circle(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;
	int			error_term;

	x = CIRCLE_RADIUS;
	y = 0;
	error_term = 0;
	while (x >= y)
	{
		circle_line(img, x, y, color);
		if (error_term <= 0)
		{
			y += 1;
			error_term += 2 * y + 1;
		}
		if (error_term > 0)
		{
			x -= 1; // check underflows
			error_term -= 2 * x + 1;
		}
	}
} */

// TODO: Polish up the light
static void	fill_circle(mlx_image_t *img, uint32_t color)
{
	uint32_t	cx;
	uint32_t	cy;
	uint32_t	x;
	uint32_t	y;

	cx = W_WIDTH / 2;
	cy = W_HEIGHT / 2;
	y = cy - CIRCLE_RADIUS;
	while (y <= cy + CIRCLE_RADIUS)
	{
		x = cx - CIRCLE_RADIUS;
		while (x <= cx + CIRCLE_RADIUS)
		{
			if (((x - cx) * (x - cx) + (y - cy) * (y - cy)) \
			<= CIRCLE_RADIUS * CIRCLE_RADIUS)
				mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

/**
 * TODO: Draw a circle in the middle of dark image and fill it with TRANSPARENCY
 */
bool	create_screen_images(t_data *data)
{
	data->torch.dark = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	if (!data->torch.dark)
		return (print_error(IMG_FAILURE, false));
	data->torch.light = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	if (!data->torch.light)
		return (print_error(IMG_FAILURE, false));
	image_fill(data->torch.dark, SHADE_COLOR);
	image_fill(data->torch.light, SHADE_COLOR);
	fill_circle(data->torch.light, TRANSPARENCY);
	mlx_image_to_window(data->mlx, data->torch.dark, 0, 0);
	mlx_image_to_window(data->mlx, data->torch.light, 0, 0);
	data->torch.light->enabled = false;
	mlx_set_instance_depth(data->torch.dark->instances, FL_DEPTH);
	mlx_set_instance_depth(data->torch.light->instances, FL_DEPTH);
	return (true);
}
