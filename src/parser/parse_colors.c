/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:10:41 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/06 14:10:44 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static uint8_t	get_next_color(char *buffer, bool reset)
{
	static int32_t	idx = 0;
	int32_t			value;

	if (reset)
		idx = 0;
	while (buffer[idx] && ft_strchr(NUMBERS, buffer[idx]) == NULL)
		idx++;
	if (buffer[idx] && ft_isdigit(buffer[idx]))
		value = ft_atoi(buffer + idx);
	else
		value = 255;
	while (buffer[idx] && ft_strchr(NUMBERS, buffer[idx]) != NULL)
		idx++;
	if (value < 0)
		return ((uint8_t)0);
	else if (value > 255)
		return ((uint8_t)255);
	return ((uint8_t)value);
}

/**
 * @brief Fetches the color data in buffer
 * @return color value im 32 bit unsigned integer
 */
uint32_t	fetch_color(char *buffer)
{
	t_color	color;

	ft_memset(&color, 0, sizeof(t_color));
	color.red = get_next_color(buffer, true);
	color.green = get_next_color(buffer, false);
	color.blue = get_next_color(buffer, false);
	color.alpha = get_next_color(buffer, false);
	return (color.red << 24 | color.green << 16 | \
	color.blue << 8 | color.alpha);
}

/**
 * @brief Creates a background image for a level from floor and ceiling colors
 * @return false on image creation failure, otherwise true
 */
bool	create_background(t_level *lvl)
{
	uint32_t	i;
	uint32_t	j;

	lvl->imgs.bg = mlx_new_image(*lvl->mlx, W_WIDTH, W_HEIGHT);
	if (!lvl->imgs.bg)
		return (print_error(IMG_FAILURE, false));
	i = 0;
	while (i < lvl->imgs.bg->height)
	{
		j = 0;
		while (j < lvl->imgs.bg->width)
		{
			if (i < lvl->imgs.bg->height / 2)
				mlx_put_pixel(lvl->imgs.bg, j, i, lvl->imgs.ceiling);
			else
				mlx_put_pixel(lvl->imgs.bg, j, i, lvl->imgs.floor);
			j++;
		}
		i++;
	}
	return (true);
}

bool	create_foreground(t_level *lvl)
{
	lvl->imgs.fg = mlx_new_image(*lvl->mlx, W_WIDTH, W_HEIGHT);
	if (!lvl->imgs.fg)
		return (print_error(IMG_FAILURE, false));
	return (true);
}
