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

uint32_t	light_level(uint32_t shade, uint32_t bright, int level)
{
	int			step;
	uint32_t	color;

	step = (shade - bright) / (LIGHT_LOD / 2);
	color = shade - (step * level);
	if (color < bright)
		color = bright;
	else if (color > shade)
		color = shade;
	return (color);
}

int	attenuation_factor(int level, float distance)
{
	float	scaled;
	int		factor;

	scaled = distance / ((float)DOF / (float)(LIGHT_LOD / 2));
	if (scaled <= 0)
		scaled = 1;
	factor = level - scaled;
	if (factor < 0)
		factor = 0;
	else if (factor > LIGHT_LOD / 2)
		factor = LIGHT_LOD / 2;
	return (factor);
}

/**
 * @brief  Calculates the current step from the edge of the light radius.
*/
int	light_step(int x, t_shade shader, int amount)
{
	int	step_size;
	int	step;
	int	iter;

	step_size = (LIGHT_RADIUS * 2) / LIGHT_LOD;
	step = 0;
	while (x > (W_WIDTH / 2 - LIGHT_RADIUS) + (step_size * (step + 1)))
		step++;
	if (step >= LIGHT_LOD / 2)
		step = LIGHT_LOD - step;
	if (step <= 0)
		step = 1;
	iter = 0;
	if (shader == INCREASE)
	{
		while (step + 1 <= (LIGHT_LOD / 2) && iter++ < amount)
			step++;
	}
	else if (shader == DECREASE)
	{
		while (step - 1 >= 0 && iter++ < amount)
			step--;
	}
	return (step);
}

/**
 * @brief Draws lighter columns on the lighting layer which simulate
 * the light of a flashight. Light varies in intensity based
 * on the radius of the light and the distance from the player
 * to the wall.
*/
void	draw_light(t_level *lvl, t_line *line, int x, float distance)
{
	int			intensity;
	uint32_t	brightness;

	if ((x < W_WIDTH / 2 - LIGHT_RADIUS || x > W_WIDTH / 2 + LIGHT_RADIUS) \
	|| lvl->data->torch.enabled == false)
		return ;
	intensity = attenuation_factor(light_step(x, NONE, 0), distance);
	brightness = light_level(SHADE_COLOR, TRANSPARENCY, intensity);
	if (line->current < W_HEIGHT)
		mlx_put_pixel(lvl->data->torch.light, x, line->current, brightness);
}
