/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_bonus_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:21:18 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/04 14:21:22 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	int	pick_door_texture(char *buffer)
{
	if (ft_strncmp(buffer, "D1", 2) == 0)
		return (DOOR1);
	else if (ft_strncmp(buffer, "D2", 2) == 0)
		return (DOOR2);
	else if (ft_strncmp(buffer, "D3", 2) == 0)
		return (DOOR3);
	else if (ft_strncmp(buffer, "D4", 2) == 0)
		return (DOOR4);
	else if (ft_strncmp(buffer, "D5", 2) == 0)
		return (DOOR5);
	else if (ft_strncmp(buffer, "D6", 2) == 0)
		return (DOOR6);
	else if (ft_strncmp(buffer, "D7", 2) == 0)
		return (DOOR7);
	return (-1);
}

static	int	pick_exit_texture(char *buffer)
{
	if (ft_strncmp(buffer, "E1", 2) == 0)
		return (EXIT1);
	else if (ft_strncmp(buffer, "E2", 2) == 0)
		return (EXIT2);
	else if (ft_strncmp(buffer, "E3", 2) == 0)
		return (EXIT3);
	else if (ft_strncmp(buffer, "E4", 2) == 0)
		return (EXIT4);
	else if (ft_strncmp(buffer, "E5", 2) == 0)
		return (EXIT5);
	else if (ft_strncmp(buffer, "E6", 2) == 0)
		return (EXIT6);
	else if (ft_strncmp(buffer, "E7", 2) == 0)
		return (EXIT7);
	return (-1);
}

static	int	pick_monster_texture(char *buffer)
{
	if (ft_strncmp(buffer, "MO", 2) == 0)
		return (MONSTER);
	return (-1);
}

int	pick_bonus_texture(char *buffer)
{
	if (pick_door_texture(buffer) > 0)
		return (pick_door_texture(buffer));
	if (pick_exit_texture(buffer) > 0)
		return (pick_exit_texture(buffer));
	if (pick_monster_texture(buffer) > 0)
		return (pick_monster_texture(buffer));
	return (-1);
}
