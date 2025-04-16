/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:25:36 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/16 13:25:41 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	next_to_door(int x, int y, t_level *lvl)
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

bool	next_to_exit(int x, int y, t_level *lvl)
{
	if (x <= 0 || x >= lvl->col_len || y <= 0 || y >= lvl->row_len)
		return (false);
	if (lvl->map[y][x] && lvl->map[y][x] == 'P')
	{
		lvl->exit.time = get_time();
		return (true);
	}
	return (false);
}

int	get_door_type(t_level *lvl, int x, int y)
{
	if (y <= 0 || x <= 0 || y >= lvl->row_len || x >= lvl->col_len)
		return (10);
	if (lvl->map[y][x] == '2')
		return (1);
	if (lvl->map[y][x] == '3')
		return (2);
	if (lvl->map[y][x] == '4')
		return (3);
	if (lvl->map[y][x] == '5')
		return (4);
	if (lvl->map[y][x] == '6')
		return (5);
	if (lvl->map[y][x] == '7')
		return (6);
	if (lvl->map[y][x] == '8')
		return (7);
	if (lvl->map[y][x] == 'P')
		return (8);
	return (0);
}
