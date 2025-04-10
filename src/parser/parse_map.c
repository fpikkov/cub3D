/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:53:39 by ahentton          #+#    #+#             */
/*   Updated: 2025/03/06 11:53:45 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	bool	find_player_pos(t_level *lvl)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (lvl->map[i])
	{
		j = 0;
		while (lvl->map[i][j])
		{
			c = lvl->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				lvl->direction = c;
				lvl->player_y = i;
				lvl->player_x = j;
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

/* Parse_map will extract the map portion from the file
*  and memorize the player direction and the position
*  via the find_player_pos function
*/

static	void	check_for_sprites(t_level *lvl)
{
	int		i;
	int		j;

	i = 0;
	while (lvl->map[i])
	{
		j = 0;
		while (lvl->map[i][j])
		{
			if (lvl->map[i][j] == '2')
				lvl->has_doors = true;
			else if (lvl->map[i][j] == 'M')
				lvl->has_monsters = true;
			else if (lvl->map[i][j] == 'P')
				lvl->has_exit = true;
			j++;
		}
		i++;
	}
}

static	void	init_monsters(t_level *lvl)
{
	int		i;
	int		j;

	i = 0;
	while (lvl->map[i])
	{
		j = 0;
		while (lvl->map[i][j])
		{
			if (lvl->map[i][j] == 'M')
			{
				lvl->monster[lvl->monster_count].y = i;
				lvl->monster[lvl->monster_count].x = j;
				lvl->monster[lvl->monster_count].active = false;
				lvl->monster[lvl->monster_count].time = get_time();
				lvl->monster_count++;
			}
			j++;
		}
		i++;
	}
}

static	void	find_exit(t_level *lvl)
{
	int		i;
	int		j;

	i = 0;
	while (lvl->map[i])
	{
		j = 0;
		while (lvl->map[i][j])
		{
			if (lvl->map[i][j] == 'P')
			{
				lvl->exit.y = i;
				lvl->exit.x = j;
			}
			j++;
		}
		i++;
	}
}

bool	parse_map(char *filename, t_data *data)
{
	t_level	*lvl;
	char	**map;

	lvl = data->levels;
	while (lvl->next)
		lvl = lvl->next;
	map = extract_map(filename);
	if (!map)
		return (false);
	lvl->map = resize_to_rectangular(map);
	lvl->map_copy = resize_to_rectangular(map);
	free_map(map);
	if (!lvl->map || !lvl->map_copy)
		return (false);
	check_for_sprites(lvl);
	if (lvl->has_monsters)
		init_monsters(lvl);
	if (lvl->has_exit)
		find_exit(lvl);
	lvl->col_len = map_col_len(lvl->map);
	lvl->row_len = map_row_len(lvl->map);
	if (!find_player_pos(lvl))
		return (print_error(MAP_NO_PLAYER, false));
	return (true);
}
