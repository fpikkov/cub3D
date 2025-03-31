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

/**
 * TODDO: pre-compute shader based on distance / DOF
 *
 * @brief Applies shading to a texture based on the ray hit distance.
 * Alpha channel is preserved as the original value.
 */
uint32_t	apply_shading(uint32_t color, float distance)
{
	uint32_t	shaded;
	float		factor[DOF] = {1.0f, 0.71f, 0.58f, 0.50f, 0.45f, 0.41f, 0.38f, 0.35f, 0.33f, 0.32f, 0.30f, 0.29f, 0.28f, 0.27f, 0.26f};
	int			idx;
/* 	if (distance < 0.1f)
		distance = 0.1f;
	else if (distance > (float)DOF)
		distance = (float)DOF;
	factor = 1.0f / sqrtf(distance);
	if (factor < 0.0f)
		factor = 0.0f;
	else if (factor > 1.0f)
		factor = 1.0f; */
	idx = 0;
	if (distance > 0.0f && distance <= (float)DOF)
		idx = distance;
	else if (distance > (float)DOF)
		idx = (float)DOF;
	shaded = 0;
	shaded |= (uint8_t)(((color >> 24) & 0xFF) * factor[idx]) << 24;
	shaded |= (uint8_t)(((color >> 16) & 0xFF) * factor[idx]) << 16;
	shaded |= (uint8_t)(((color >> 8) & 0xFF) * factor[idx]) << 8;
	shaded |= (uint8_t)(color & 0xFF);
	return (shaded);
}
