/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:40:59 by ahentton          #+#    #+#             */
/*   Updated: 2025/03/06 13:41:05 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

static	bool	check_unknown_characters(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if (!ft_strchr("01NSEW", map[i]))
			return (false);
		else
			i++;
	}
	return (true);
}

static	bool	check_single_player(char **map)
{
	int		i;
	int		player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strchr("NSEW", map[i]))
			player_count++;
		i++;
	}
	if (player_count != 1)
		return (false);

	return (true);
}

static	bool	check_if_close(char **map, int y, int x)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	if (!check_if_close(map, y - 1, x))
		return (false);
	if (!check_if_close(map, y + 1, x))
		return (false);
	if (!check_if_close(map, y, x - 1))
		return (false);
	if (!check_if_close(map, y, x + 1))
		return (false);
	map[y][x] = 'X';
	return (true);
}

bool	validate_map(t_data *data)
{
	t_level *lvl;

	lvl = data->levels;
	while (lvl->next)
		lvl = lvl->next;
	if (!check_unknown_characters(lvl->map))
	{
		print_error(MAP_UNKNOWN_CHARACTERS);
		return (false);
	}
	if (!check_single_player(lvl->map))
	{
		print_error(MAP_TOO_MANY_PLAYERS);
		return (false);
	}
	if (!check_if_closed(lvl->map_copy, lvl->player_y, lvl->player_x))
	{
		print_error(MAP_NOT_CLOSED);
		return (false);
	}
	return (true);
}
