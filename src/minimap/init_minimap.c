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

static	void	find_starting_tile(t_minimap *map)
{
	if (map->width - player_x < 5)
		map->start_x = map->player_x - (map->range * 2 - (map->width - map->player_x - 1));
	else if (map->player_x - map->range < 0)
		map->start_x = map->range + (map->player_x - map->range - 1);
	else
		map->start_x = map->player_x - map->range;
	if (map->height - map->player_y < 5)
		map->start_y = map->player_y - (map->range * 2 - (map->height - player_y - 1));
	else if (player_y - map->range < 0)
		map->start_y = map->range + (map->player_x - map->range - 1);
	else
		map->start_y = map->player_y - map->range;
}
void	init_data(t_minimap *map)
{
	ft_memset(map, 0, sizeof(t_minimap));
	map->range = 5;
	map->tile_size = 256.0 / (map->range * 2 + 1);
	find_starting_tile(map);
}
