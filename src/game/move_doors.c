/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:26:38 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/04 12:26:44 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	void	open_door(t_level *lvl)
{
	if (lvl->door.status == OPENING1)
		lvl->map[lvl->door.y][lvl->door.x] = '3';
	else if (lvl->door.status == OPENING2)
		lvl->map[lvl->door.y][lvl->door.x] = '4';
	else if (lvl->door.status == OPENING3)
		lvl->map[lvl->door.y][lvl->door.x] = '5';
	else if (lvl->door.status == OPENING4)
		lvl->map[lvl->door.y][lvl->door.x] = '6';
	else if (lvl->door.status == OPENING5)
		lvl->map[lvl->door.y][lvl->door.x] = '7';
	if (lvl->door.status == OPEN)
		lvl->map[lvl->door.y][lvl->door.x] = '8';
	else
	{
		lvl->door.status++;
		lvl->door.time = get_time();
	}
}

static	void	close_door(t_level *lvl)
{
	if (lvl->door.status == CLOSING1)
		lvl->map[lvl->door.y][lvl->door.x] = '7';
	else if (lvl->door.status == CLOSING2)
		lvl->map[lvl->door.y][lvl->door.x] = '6';
	else if (lvl->door.status == CLOSING3)
		lvl->map[lvl->door.y][lvl->door.x] = '5';
	else if (lvl->door.status == CLOSING4)
		lvl->map[lvl->door.y][lvl->door.x] = '4';
	else if (lvl->door.status == CLOSING5)
		lvl->map[lvl->door.y][lvl->door.x] = '3';
	if (lvl->door.status > CLOSING5)
	{
		lvl->map[lvl->door.y][lvl->door.x] = '2';
		ft_memset(&lvl->door, 0, sizeof(t_door));
	}
	else
	{
		lvl->door.status++;
		lvl->door.time = get_time();
	}
}

void	move_door(t_level *lvl)
{
	if (lvl->door.status > CLOSED \
	&& lvl->door.status <= OPEN \
	&& get_time() - lvl->door.time >= 150)
		open_door(lvl);
	if (lvl->door.status == OPEN && get_time() - lvl->door.time >= 2500 \
	&& (lvl->player_x != lvl->door.x || lvl->player_y != lvl->door.y))
		lvl->door.status++;
	else if (lvl->door.status > OPEN \
	&& get_time() - lvl->door.time >= 150)
		close_door(lvl);
}

void	open_exit(t_level *lvl)
{
	if (lvl->exit.status > CLOSED \
	&& lvl->exit.status < OPEN \
	&& get_time() - lvl->door.time >= 200)
	{
		lvl->exit.status++;
		lvl->exit.time = get_time();
	}
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
	else if (next_to_exit(data->player.x - 1, data->player.y, lvl)
		|| next_to_exit(data->player.x + 1, data->player.y, lvl)
		|| next_to_exit(data->player.x, data->player.y - 1, lvl)
		|| next_to_exit(data->player.x, data->player.y + 1, lvl))
		lvl->exit.status = OPENING1;
}
