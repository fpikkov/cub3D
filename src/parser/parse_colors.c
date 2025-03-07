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

static uint32_t	fetch_colors(char *buffer)
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

static void	set_colors(mlx_image_t *img, uint32_t value)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, value);
			j++;
		}
		i++;
	}
}

static bool	create_color(uint32_t value, t_level *lvl, int dir)
{
	if (dir == FLOOR)
	{
		if (lvl->imgs.floor)
			print_error(TEXTURE_DUPLICATE, true);
		else
			lvl->imgs.floor = mlx_new_image(*lvl->mlx, W_WIDTH, W_HEIGHT / 2);
		if (!lvl->imgs.floor)
			return (print_error(TEXTURE_FAILURE, false));
		set_colors(lvl->imgs.floor, value);
	}
	else if (dir == CEILING)
	{
		if (lvl->imgs.ceiling)
			print_error(TEXTURE_DUPLICATE, true);
		else
			lvl->imgs.ceiling = \
			mlx_new_image(*lvl->mlx, W_WIDTH, W_HEIGHT / 2);
		if (!lvl->imgs.ceiling)
			return (print_error(TEXTURE_FAILURE, false));
		set_colors(lvl->imgs.ceiling, value);
	}
	return (true);
}

bool	load_color(char *buffer, t_level *lvl, int direction)
{
	uint32_t	value;

	value = fetch_colors(buffer);
	if (!create_color(value, lvl, direction))
		return (false);
	return (true);
}
