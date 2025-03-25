/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:33:35 by ahentton          #+#    #+#             */
/*   Updated: 2025/03/21 16:33:40 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//init_minimap initializes and inherits data,
//which is used to draw the minimap correctly.
//Map width, map height, and player coordinates are crucial information.
//Range and tile_size are subject to change later, when scaling is included.
//TODO:: Make range and tile_size compatible for scaling of the minimap.
bool	init_minimap(t_data *data)
{
	ft_memset(&data->minimap, 0, sizeof(t_minimap));
	data->minimap.img = mlx_new_image(data->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!data->minimap.img)
		return (print_error(IMG_FAILURE, false));
	data->minimap.tile_size = MINIMAP_SIZE / (RANGE * 2 + 1);
	mlx_image_to_window(data->mlx, data->minimap.img, 10, 10);
	mlx_set_instance_depth(data->minimap.img->instances, MM_DEPTH);
	return (true);
}
