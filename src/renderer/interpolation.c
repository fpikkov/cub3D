/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:47:37 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/17 11:47:38 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Uses nearest neighbor interpolation to return a color value closest
 * to the target image size's grid. The x and y have to be converted to bytes
 * as the color data is fetched from a pointer that gets incremented.
 * @param[in] tex the texture where to fetch color values from
 * @param[in] x the target image's x pixel co-ordinate
 * @param[in] y the target image's y pixel co-ordinate
 * @return 32 bit color value
 */
uint32_t	nearest_neighbor(mlx_texture_t *tex, uint32_t x, uint32_t y)
{
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	color;
	uint8_t		*ptr;

	src_x = (uint32_t)(((float)x / TILE) * tex->width);
	src_y = (uint32_t)(((float)y / TILE) * tex->height);
	ptr = &tex->pixels[(src_y * tex->width + src_x) * tex->bytes_per_pixel];
	color = 0;
	color |= *ptr << 24;
	ptr++;
	color |= *ptr << 16;
	ptr++;
	color |= *ptr << 8;
	ptr++;
	color |= *ptr;
	return (color);
}

uint32_t	sprite_interpolation(mlx_texture_t *tex, float x, uint32_t y)
{
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	color;
	uint8_t		*ptr;

	src_x = (uint32_t)(x * tex->width);
	if (src_x >= tex->width)
		src_x = tex->width - 1;
	src_y = (uint32_t)(((float)y / TILE) * tex->height);
	if (src_y >= tex->height)
		src_y = tex->height - 1;
	ptr = &tex->pixels[(src_y * tex->width + src_x) * tex->bytes_per_pixel];
	color = 0;
	color |= *ptr << 24;
	ptr++;
	color |= *ptr << 16;
	ptr++;
	color |= *ptr << 8;
	ptr++;
	color |= *ptr;
	return (color);
}

int	scale_texture_height(t_line *line)
{
	return (((line->current - line->start) * (TILE - 1)) / line->delta);
}
