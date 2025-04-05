/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_of_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:57:19 by fpikkov           #+#    #+#             */
/*   Updated: 2025/04/04 15:57:20 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_fog(t_ray *ray, t_level *lvl, int x)
{
	t_line		line;

	ft_memset(&line, 0, sizeof(t_line));
	line_init(&line, ray->distance);
	while (line.current <= line.end)
	{
		if (line.current < 0)
			line.current = 0;
		if (line.current >= W_HEIGHT)
			break ;
		mlx_put_pixel(lvl->imgs.fg, x, line.current, FOG_COLOR);
		line.current++;
	}
	light_floor(lvl, &line, x);
}
