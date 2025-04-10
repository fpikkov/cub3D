/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:40:29 by fpikkov           #+#    #+#             */
/*   Updated: 2025/04/08 16:40:30 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	sprite_init(mlx_t *mlx, mlx_image_t *img, bool active, int32_t z)
{
	uint32_t	offset;

	offset = LIGHT_LOD / 4;
	if (!mlx_resize_image(img, FL_IMG_SIZE, FL_IMG_SIZE))
		(void)print_error(IMG_RESIZE_FAILURE, true);
	mlx_image_to_window(mlx, img, (W_WIDTH / 2) - (img->width / 2) - offset, \
	W_HEIGHT - img->height);
	mlx_set_instance_depth(img->instances, z);
	if (!active)
		img->enabled = !img->enabled;
}

void	fl_sprite_setup(t_data *data)
{
	sprite_init(data->mlx, data->torch.off, true, MM_DEPTH);
	sprite_init(data->mlx, data->torch.one, false, MM_DEPTH);
	sprite_init(data->mlx, data->torch.two, false, MM_DEPTH);
	sprite_init(data->mlx, data->torch.three, false, MM_DEPTH);
	sprite_init(data->mlx, data->torch.four, false, MM_DEPTH);
	sprite_init(data->mlx, data->torch.five, false, MM_DEPTH);
	data->torch.battery = BATTERY_MAX;
}
