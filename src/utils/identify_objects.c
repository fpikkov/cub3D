/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:46:07 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/01 13:46:13 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Checks if the given co-ordinates reached a wall/door or out of bounds
 */
bool	is_wall(t_level	*lvl, int x, int y)
{
	if (y <= 0 || x <= 0 || y >= lvl->row_len || x >= lvl->col_len)
		return (true);
	if (lvl->map[y][x] == '1')
		return (true);
	return (false);
}

bool	is_closed_door(t_level *lvl, int x, int y)
{
	if (y <= 0 || x <= 0 || y >= lvl->row_len || x >= lvl->col_len)
		return (true);
	else if ((lvl->map[y][x] >= '2' && lvl->map[y][x] <= '7') \
	|| (lvl->map[y][x] == 'P' && lvl->exit.status != OPEN))
		return (true);
	return (false);
}

int	get_sprite_type(t_level *lvl, int x, int y)
{
	if (y <= 0 || x <= 0 || y >= lvl->row_len || x >= lvl->col_len)
		return (0);
	if (lvl->map[y][x] == 'M')
		return (1);
	return (0);
}
