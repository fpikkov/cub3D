/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_floor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:12:00 by fpikkov           #+#    #+#             */
/*   Updated: 2025/04/02 14:12:02 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * NOTE: I had to pack x and y screnspace co-ordinates into a single value
 * to work around the norm.
 *
 * @brief Draws light onto the floor while making it fade out towards
*/
/* static void	shade_floor(t_level *lvl, int packed_axis, int size, int distance)
{
	int			x;
	int			y;
	int			step_y;
	int			step_size_y;
	int			max_intensity;
	int			min_intensity;
	int			intensity_delta;
	uint32_t	brightness;

	unpack_shorts(&x, &y, packed_axis);
	step_size_y = (W_HEIGHT - y) / size;
	step_y = 0;
	max_intensity = attenuation_factor(light_step(x, size), distance);
	min_intensity = attenuation_factor(light_step(x, size), (float)DOF);
	intensity_delta = (max_intensity - min_intensity) / step_size_y;
	brightness = light_level(SHADE_COLOR, TRANSPARENCY, max_intensity);
	while (y < W_HEIGHT)
	{
		if (y >= (W_HEIGHT - y) + (step_size_y * (step_y + 1)) \
		&& max_intensity - intensity_delta >= 0)
		{
			brightness = light_level(SHADE_COLOR, TRANSPARENCY, max_intensity + intensity_delta);
			step_y++;
		}
		if (brightness == SHADE_COLOR)
			break ;
		mlx_put_pixel(lvl->data->torch.light, x, y, brightness);
		y++;
	}
} */

static void	shade_floor(t_level *lvl, int packed_axis, int size, float distance)
{
	int			x;
	int			y;
	int			step_y;
	int			step_size_y;
	int			intensity;
	uint32_t	brightness;

	unpack_shorts(&x, &y, packed_axis);
	step_size_y = (W_HEIGHT - y) / LIGHT_LOD;
	step_y = 0;
	while (y < W_HEIGHT)
	{
		intensity = attenuation_factor(light_step(x + (step_y / LIGHT_LOD), size), distance + (step_y / LIGHT_LOD));
		if (intensity < 0)
			intensity = 0;
		brightness = light_level(SHADE_COLOR, TRANSPARENCY, intensity);
		if (y >= (W_HEIGHT - y) + (step_size_y * (step_y + 1)))
			step_y++;
		if (brightness == SHADE_COLOR)
			break ;
		mlx_put_pixel(lvl->data->torch.light, x, y, brightness);
		y++;
	}
}

void light_floor(t_level *lvl, t_line *line, int x, float distance)
{
	int			step_size;

	if ((x < W_WIDTH / 2 - LIGHT_RADIUS || x > W_WIDTH / 2 + LIGHT_RADIUS) \
	|| lvl->data->torch.enabled == false)
		return ;
	if (line->current != line->end && line->current >= W_HEIGHT)
		return ;
	step_size = (LIGHT_RADIUS * 2) / LIGHT_LOD;
	shade_floor(lvl, pack_shorts(x, line->current), step_size, distance);

}
