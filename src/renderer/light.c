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

/**
 * TODO: Light should have a warm tone
 */
/* static void	fill_circle(mlx_image_t *img, uint32_t radius, uint32_t color)
{
	uint32_t	cx;
	uint32_t	cy;
	uint32_t	x;
	uint32_t	y;

	cx = (W_WIDTH / 2) - (W_WIDTH / 24); // Circle middle X is sllightly off-center towards the left
	cy = (W_HEIGHT / 2); // Circle middle Y is the center of the screen
	y = cy - radius;
	while (y <= cy + radius)
	{
		x = cx - radius;
		while (x <= cx + radius)
		{
			if ((((x - cx) * (x - cx) + (y - cy) * (y - cy)) \
			<= radius * radius) && (x >= 0 && x < img->width) \
			&& (y >= 0 && y < img->height))
				mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
} */

/**
 * TODO: Refactor code
 */
/* static float	average_distance(t_player *p, t_level *lvl, uint32_t radius, uint32_t size, uint32_t cx)
{
	t_ray		ray;
	uint32_t	sample_x;
	uint32_t	sample_size;
	float		average;
	float		count;

	ft_memset(&ray, 0, sizeof(t_ray));
	count = 0.0f;
	average = 0.0f;
	sample_size = size / SAMPLE_SIZE; // How much to increment x
	sample_x = cx + radius - size;
	while (sample_x <= cx + radius)
	{
		raycast(&ray, lvl, p, sample_x);
		average += ray.distance;
		raycast(&ray, lvl, p, radius - sample_x);
		average += ray.distance;
		count += 2.0f;
		sample_x += sample_size;
	}
	average /= count;
	return (average);
} */

/**
 * NOTE: Circle step defines how many light circles to draw
 *
 * TODO: Refactor code
 * TODO: Create a color manager which will attenuate the light intensity level
 * based on how far the circle is from the edge of the max radius and how far
 * the ray hit the wall.
 *
 * NOTE: increase in distance = decrease in brightness
 * NOTE: decrease in radius = increase in brightness
 */
/* void	render_light(t_data *data, t_level *lvl)
{
	uint32_t	radius;
	uint32_t	scaled;
	uint32_t	step_size;
	uint32_t	cx;
	float		distance;
	uint32_t	color;
	uint32_t	color_step;

	color = SHADE_COLOR;
	color_step = SHADE_COLOR / CIRCLE_STEP;
	cx = (W_WIDTH / 2) - (W_WIDTH / 24);
	image_fill(data->torch.light, SHADE_COLOR);
	radius = CIRCLE_RADIUS; // First circle
	step_size = CIRCLE_RADIUS / CIRCLE_STEP; // How many circles to draw
	while (radius >= step_size)
	{
		distance = average_distance(&data->player, lvl, radius, step_size, cx);
		scaled = distance * (float)radius;
		fill_circle(data->torch.light, scaled, color);
		color -= color_step;
		radius -= step_size;
	}
} */

void	draw_light(t_level *lvl, t_line *line, int x)
{
	if ((x < (W_WIDTH / 2) - (int)CIRCLE_RADIUS \
	|| x > (W_WIDTH / 2) + (int)CIRCLE_RADIUS) \
	|| lvl->data->torch.enabled == false)
		return ;
	mlx_put_pixel(lvl->data->torch.light, x, line->current, TRANSPARENCY);

}
