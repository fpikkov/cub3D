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
