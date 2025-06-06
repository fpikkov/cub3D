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

static void	shade_floor(t_level *lvl, int x, int y)
{
	int			step_y;
	int			step_x;
	int			step_size_y;
	uint32_t	brightness;

	step_size_y = W_HEIGHT / LIGHT_LOD;
	step_y = 0;
	step_x = light_step(x, NONE, 0);
	while (y < W_HEIGHT)
	{
		while (y >= W_HEIGHT - 100 - (step_size_y * (LIGHT_LOD / 2 - step_y)))
		{
			step_y++;
			step_x = light_step(x, DECREASE, step_y >> 1);
		}
		if (step_x == 0)
			break ;
		brightness = light_level(SHADE_COLOR, TRANSPARENCY, \
		(step_x + (W_HEIGHT / 2 / step_size_y) / step_y) / 2);
		mlx_put_pixel(lvl->data->torch.light, x, y, brightness);
		y++;
	}
}

/**
 * NOTE: The floor lighting does not currently take into account the
 * distance to the wall nor the alpha layer of the wall.
 *
 * @brief Lights up the floor in the flashlight direction.
 */
void	light_floor(t_level *lvl, t_line *line, int x)
{
	if ((x < W_WIDTH / 2 - LIGHT_RADIUS || x > W_WIDTH / 2 + LIGHT_RADIUS) \
	|| lvl->data->torch.enabled == false)
		return ;
	if (line->current != line->end && line->current >= W_HEIGHT)
		return ;
	shade_floor(lvl, x, line->current);
}
