/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_door_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:21:18 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/04 14:21:22 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	load_door_texture(mlx_texture_t *tex, t_level *lvl, int type)
{
	lvl->doored = true;
	if (type == DOOR1 && !lvl->textures.door1)
		lvl->textures.door1 = tex;
	else if (type == DOOR2 && !lvl->textures.door2)
		lvl->textures.door2 = tex;
	else if (type == DOOR3 && !lvl->textures.door3)
		lvl->textures.door3 = tex;
	else if (type == DOOR4 && !lvl->textures.door4)
		lvl->textures.door4 = tex;
	else if (type == DOOR5 && !lvl->textures.door5)
		lvl->textures.door5 = tex;
	else if (type == DOOR6 && !lvl->textures.door6)
		lvl->textures.door6 = tex;
	else if (type == DOOR7 && !lvl->textures.door7)
		lvl->textures.door7 = tex;
	else
		mlx_delete_texture(tex);
}

bool	is_door_texture(char *buffer, int idx, t_level *lvl)
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
