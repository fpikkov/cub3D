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

//find_starting_tile finds the starting tile for drawing the minimap,
//by using the range(amount of tiles player is able to see in minimap,
//in each direction) and player location in the calculations.
//If distance between player and outer wall is less than the range,
//rendering starts further away in the opposite direction,
//to keep minimap inside the playable level.
static void	find_starting_tile(t_minimap *map, int player_x, int player_y)
{
	if (map->width - player_x < 5)
		map->start_x = player_x - (RANGE * 2 - (map->width - player_x - 1));
	else if (player_x - RANGE <= 0)
		map->start_x = 0;
	else
		map->start_x = player_x - RANGE;
	if (map->height - player_y <= 5)
		map->start_y = player_y - (RANGE * 2 - (map->height - player_y - 1));
	else if (player_y - RANGE <= 0)
		map->start_y = 0;
	else
		map->start_y = player_y - RANGE;
}

static	void	inherit_player_data(t_minimap *map, t_player *player)
{
	map->player_x = player->x;
	map->player_y = player->y;
	map->player_angle = player->angle;
}

void	update_minimap(t_data *data, t_level *lvl)
{
	data->minimap.height = lvl->row_len;
	data->minimap.width = lvl->col_len;
	data->minimap.map = lvl->map;
	find_starting_tile(&data->minimap, data->player.x, data->player.y);
	inherit_player_data(&data->minimap, &data->player);
	draw_minimap(&data->minimap);
}
