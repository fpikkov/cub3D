/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:24 by ahentton          #+#    #+#             */
/*   Updated: 2025/03/24 14:16:31 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	load_minimap(t_data *data)
{
	init_minimap(data);
	draw_minimap(data->minimap);
	mlx_image_to_window(data->mlx, data->minimap.img, 10, 10);
}
