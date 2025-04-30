/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bonus_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:43:17 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/16 13:43:21 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	bool	save_door_texture(mlx_texture_t *tex, t_level *lvl, int type)
{
	if (type == DOOR1)
		return (save_texture(&lvl->textures.door1, tex));
	else if (type == DOOR2)
		return (save_texture(&lvl->textures.door2, tex));
	else if (type == DOOR3)
		return (save_texture(&lvl->textures.door3, tex));
	else if (type == DOOR4)
		return (save_texture(&lvl->textures.door4, tex));
	else if (type == DOOR5)
		return (save_texture(&lvl->textures.door5, tex));
	else if (type == DOOR6)
		return (save_texture(&lvl->textures.door6, tex));
	else if (type == DOOR7)
		return (save_texture(&lvl->textures.door7, tex));
	return (true);
}

static	bool	save_exit_texture(mlx_texture_t *tex, t_level *lvl, int type)
{
	if (type == EXIT1)
		return (save_texture(&lvl->textures.exit1, tex));
	else if (type == EXIT2)
		return (save_texture(&lvl->textures.exit2, tex));
	else if (type == EXIT3)
		return (save_texture(&lvl->textures.exit3, tex));
	else if (type == EXIT4)
		return (save_texture(&lvl->textures.exit4, tex));
	else if (type == EXIT5)
		return (save_texture(&lvl->textures.exit5, tex));
	else if (type == EXIT6)
		return (save_texture(&lvl->textures.exit6, tex));
	else if (type == EXIT7)
		return (save_texture(&lvl->textures.exit7, tex));
	return (true);
}

static	bool	save_monster_texture(mlx_texture_t *tex, t_level *lvl, int type)
{
	if (type == MONSTER)
		return (save_texture(&lvl->textures.monster, tex));
	return (true);
}

bool	save_bonus_texture(mlx_texture_t *tex, t_level *lvl, int type)
{
	if (type >= DOOR1 && type <= DOOR7)
		return (save_door_texture(tex, lvl, type));
	else if (type >= EXIT1 && type <= EXIT7)
		return (save_exit_texture(tex, lvl, type));
	else if (type == MONSTER)
		return (save_monster_texture(tex, lvl, type));
	return (true);
}
