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
 * TODO: How much to attentuate based on y location. Currently it does not scale
 * even linearly. Ideally intensity_y would scale inversely to the step_y.
 *
 * TODO: Fix cone not being rendered when the raycaster hits DOF limit.
*/
static void	shade_floor(t_level *lvl, int x, int y)
{
	int			step_y;
	int			step_x;
	int			step_size_y;
	float		intensity_y;
	uint32_t	brightness;
	int			average;

	step_size_y = W_HEIGHT / LIGHT_LOD;
	step_y = 0;
	step_x = light_step(x, NONE, 0);
	while (y < W_HEIGHT)
	{
		while (y >= W_HEIGHT - (step_size_y * (LIGHT_LOD / 2 - step_y)))
		{
			step_y++;
			step_x = light_step(x, DECREASE, step_y / 2);
		}
		intensity_y = step_size_y / (1 + (2 * step_y)); // TODO: How much to attentuate based on y location
		average = (step_x + intensity_y) / 2;
		if (brightness == SHADE_COLOR)
			break ;
		brightness = light_level(SHADE_COLOR, TRANSPARENCY, average);
		mlx_put_pixel(lvl->data->torch.light, x, y, brightness);
		y++;
	}
}

void light_floor(t_level *lvl, t_line *line, int x)
{
	if ((x < W_WIDTH / 2 - LIGHT_RADIUS || x > W_WIDTH / 2 + LIGHT_RADIUS) \
	|| lvl->data->torch.enabled == false)
		return ;
	if (line->current != line->end && line->current >= W_HEIGHT)
		return ;
	shade_floor(lvl, x, line->current);

}
