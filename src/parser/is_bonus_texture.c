/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bonus_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:21:18 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/04 14:21:22 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	bool	is_door_texture(char *buffer, int idx, t_level *lvl)
{
	if (ft_strncmp(buffer + idx, "D1", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, DOOR1));
	else if (ft_strncmp(buffer + idx, "D2", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, DOOR2));
	else if (ft_strncmp(buffer + idx, "D3", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, DOOR3));
	else if (ft_strncmp(buffer + idx, "D4", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, DOOR4));
	else if (ft_strncmp(buffer + idx, "D5", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, DOOR5));
	else if (ft_strncmp(buffer + idx, "D6", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, DOOR6));
	else if (ft_strncmp(buffer + idx, "D7", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, DOOR7));
	return (true);
}

static	bool	is_exit_texture(char *buffer, int idx, t_level *lvl)
{
	if (ft_strncmp(buffer + idx, "E1", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, EXIT1));
	else if (ft_strncmp(buffer + idx, "E2", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, EXIT2));
	else if (ft_strncmp(buffer + idx, "E3", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, EXIT3));
	else if (ft_strncmp(buffer + idx, "E4", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, EXIT4));
	else if (ft_strncmp(buffer + idx, "E5", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, EXIT5));
	else if (ft_strncmp(buffer + idx, "E6", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, EXIT6));
	else if (ft_strncmp(buffer + idx, "E7", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, EXIT7));
	return (true);
}

static	bool	is_monster_texture(char *buffer, int idx, t_level *lvl)
{
	if (ft_strncmp(buffer + idx, "MO", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, MONSTER));
	return (true);
}

bool	is_bonus_texture(char *buffer, int idx, t_level *lvl)
{
	if (!is_door_texture(buffer, idx, lvl))
		return (false);
	if (!is_exit_texture(buffer, idx, lvl))
		return (false);
	if (!is_monster_texture(buffer, idx, lvl))
		return (false);
	return (true);
}
