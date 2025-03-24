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

//find_starting_tile finds the starting tile for drawing the minimap,
//by using the range(amount of tiles player is able to see in minimap,
//in each direction) and player location in the calculations.
//If distance between player and outer wall is less than the range,
//rendering starts further away in the opposite direction,
//to keep minimap inside the playable level.
static	void	find_starting_tile(t_minimap *map, int player_x, int player_y)
{
	if (map->width - player_x < 5)
		map->start_x = player_x - (map->range * 2 - (map->width - player_x - 1));
	else if (player_x - map->range < 0)
		map->start_x = map->range + (player_x - map->range - 1);
	else
		map->start_x = player_x - map->range;
	if (map->height - player_y < 5)
		map->start_y = player_y - (map->range * 2 - (map->height - player_y - 1));
	else if (player_y - map->range < 0)
		map->start_y = map->range + (player_x - map->range - 1);
	else
		map->start_y = player_y - map->range;
}
//init_minimap initializes and inherits data,
//which is used to draw the minimap correctly.
//Map width, map height, and player coordinates are crucial information.
//Range and tile_size are subject to change later, when scaling is included.
//TODO:: Make range and tile_size compatible for scaling of the minimap.
static	void	init_minimap(t_data *data)
{
	ft_memset(&data->minimap, 0, sizeof(t_minimap));
	data->minimap.height = data->levels->row_len;
	data->minimap.width = data->levels->col_len;
	data->minimap.map = data->levels->map;
	data->minimap.range = 5;
	data->minimap.tile_size = 256.0 / (data->minimap.range * 2 + 1);
	find_starting_tile(&data->minimap, data->player.x, data->player.y);
}
