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

#include "cube.h"

static	bool	check_unknown_characters(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("01234567MRNSEW", map[i][j]))
				return (false);
			else
				j++;
		}
		i++;
	}
	return (true);
}

static	bool	check_single_player(char **map)
{
	int		i;
	int		j;
	int		player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				map[i][j] = '0';
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (false);
	return (true);
}

static	bool	check_if_closed(char **map, int y, int x)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (true);
	map[y][x] = 'X';
	if (!check_if_closed(map, y - 1, x))
		return (false);
	if (!check_if_closed(map, y + 1, x))
		return (false);
	if (!check_if_closed(map, y, x - 1))
		return (false);
	if (!check_if_closed(map, y, x + 1))
		return (false);
	return (true);
}

bool	validate_map(t_data *data)
{
	t_level	*lvl;

	lvl = data->levels;
	while (lvl->next)
		lvl = lvl->next;
	if (!check_unknown_characters(lvl->map))
		return (print_error(MAP_UNKNOWN_CHARACTERS, false));
	if (!check_single_player(lvl->map))
		return (print_error(MAP_TOO_MANY_PLAYERS, false));
	if (!check_if_closed(lvl->map_copy, lvl->player_y, lvl->player_x))
		return (print_error(MAP_NOT_CLOSED, false));
	return (true);
}
