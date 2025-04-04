/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:26:38 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/04 12:26:44 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	bool	next_to_door(int x, int y, t_level *lvl)
{
	if (x <= 0 || x >= lvl->col_len || y <= 0 || y >= lvl->row_len)
		return (false);
	if (lvl->map[y][x] && lvl->map[y][x] == '2')
	{
		lvl->door.x = x;
		lvl->door.y = y;
		lvl->door.time = get_time();
		return (true);
	}
	return (false);
}

void	door_action(t_data *data)
{
	t_level	*lvl;

	lvl = current_level(data);
	if (next_to_door(data->player.x - 1, data->player.y, lvl)
		|| next_to_door(data->player.x + 1, data->player.y, lvl)
		|| next_to_door(data->player.x, data->player.y - 1, lvl)
		|| next_to_door(data->player.x, data->player.y + 1, lvl))
		lvl->door.status = OPENING1;
}

void	move_door(t_level *instance)
{
	if (get_time() - instance->door.time >= 200)
	{
		if (instance->door.status == OPENING1)
			instance->map[instance->door.y][instance->door.x] = '3';
		else if (instance->door.status == OPENING2)
			instance->map[instance->door.y][instance->door.x] = '4';
		else if (instance->door.status == OPENING3)
			instance->map[instance->door.y][instance->door.x] = '5';
		else if (instance->door.status == OPENING4)
			instance->map[instance->door.y][instance->door.x] = '6';
		else if (instance->door.status == OPENING5)
			instance->map[instance->door.y][instance->door.x] = '7';
		if (instance->door.status == OPEN)
		{
			instance->map[instance->door.y][instance->door.x] = '8';
			ft_memset(&instance->door, 0, sizeof(t_door));
		}
		else
		{
			instance->door.status++;
			instance->door.time = get_time();
		}
	}
}
