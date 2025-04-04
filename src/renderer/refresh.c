/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:21:34 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/07 16:21:35 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	reset_foreground(t_level *lvl)
{
	if (lvl->imgs.fg)
	{
		ft_memset(lvl->imgs.fg->pixels, 0, \
		lvl->imgs.fg->width * lvl->imgs.fg->height * sizeof(int32_t));
	}
	if (lvl->data->torch.light)
		image_fill(lvl->data->torch.light, SHADE_COLOR);
}

/**
 * @brief Fills the whole given image with a single color
 */
void	image_fill(mlx_image_t *img, uint32_t color)
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
