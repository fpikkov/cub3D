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

static uint8_t	get_next_color(char *buffer, t_channel channel, bool *fail)
{
	static int32_t	idx = 0;
	uint8_t			value;

	value = 255;
	if (channel == C_EXTRA)
		return (extra_colors(buffer, idx, fail));
	if (channel == C_RED)
		idx = 0;
	while (buffer[idx] && ft_strchr(NUMBERS, buffer[idx]) == NULL)
	{
		*fail = color_warning(buffer[idx]);
		if (*fail == true)
			return (value);
		idx++;
	}
	if (buffer[idx])
		value = arg_to_uchar(buffer + idx, fail);
	if (*fail == true)
		return (value);
	if (!buffer[idx] && channel != C_ALPHA)
		*fail = !print_error(IMG_COLOR_MISSING, false);
	while (buffer[idx] && ft_strchr(NUMBERS, buffer[idx]) != NULL)
		idx++;
	return (value);
}

/**
 * @brief Fetches the color data in buffer
 * @return color value im 32 bit unsigned integer
 */
uint32_t	fetch_color(char *buffer, bool *fail)
{
	t_color	color;

	ft_memset(&color, 0, sizeof(t_color));
	color.red = get_next_color(buffer, C_RED, fail);
	if (*fail == true)
		return (0);
	color.green = get_next_color(buffer, C_GREEN, fail);
	if (*fail == true)
		return (0);
	color.blue = get_next_color(buffer, C_BLUE, fail);
	if (*fail == true)
		return (0);
	color.alpha = get_next_color(buffer, C_ALPHA, fail);
	if (*fail == true)
		return (0);
	(void)get_next_color(buffer, C_EXTRA, fail);
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

bool	create_screen_images(t_data *data)
{
	data->torch.dark = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	if (!data->torch.dark)
		return (print_error(IMG_FAILURE, false));
	data->torch.light = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	if (!data->torch.light)
		return (print_error(IMG_FAILURE, false));
	image_fill(data->torch.dark, SHADE_COLOR);
	image_fill(data->torch.light, SHADE_COLOR);
	mlx_image_to_window(data->mlx, data->torch.dark, 0, 0);
	mlx_image_to_window(data->mlx, data->torch.light, 0, 0);
	data->torch.light->enabled = false;
	mlx_set_instance_depth(data->torch.dark->instances, FL_DEPTH);
	mlx_set_instance_depth(data->torch.light->instances, FL_DEPTH);
	return (true);
}
