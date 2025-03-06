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
bool	parse_map(char *filename, t_data *data)
{
	t_level	*lvl;

	lvl = data->levels;
	while (lvl->next)
		lvl = lvl->next;
	lvl->map = extract_map(filename);
	lvl->map_copy = extract_map(filename);
	if (!lvl->map || !lvl->map_copy)
		return (false);
	if (!find_player_pos(lvl))
	{
		print_error(MAP_NO_PLAYER);
		return (false);
	}
	return (true);
}
