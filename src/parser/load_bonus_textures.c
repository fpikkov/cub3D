/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bonus_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:43:17 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/16 13:43:21 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	void	load_door_texture(mlx_texture_t *tex, t_level *lvl, int type)
{
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

static	void	load_exit_texture(mlx_texture_t *tex, t_level *lvl, int type)
{
	if (type == EXIT1 && !lvl->textures.exit1)
		lvl->textures.exit1 = tex;
	else if (type == EXIT2 && !lvl->textures.exit2)
		lvl->textures.exit2 = tex;
	else if (type == EXIT3 && !lvl->textures.exit3)
		lvl->textures.exit3 = tex;
	else if (type == EXIT4 && !lvl->textures.exit4)
		lvl->textures.exit4 = tex;
	else if (type == EXIT5 && !lvl->textures.exit5)
		lvl->textures.exit5 = tex;
	else if (type == EXIT6 && !lvl->textures.exit6)
		lvl->textures.exit6 = tex;
	else if (type == EXIT7 && !lvl->textures.exit7)
		lvl->textures.exit7 = tex;
	else
		mlx_delete_texture(tex);
}

static	void	load_monster_texture(mlx_texture_t *tex, t_level *lvl, int type)
{
	if (type == MONSTER && !lvl->textures.monster)
		lvl->textures.monster = tex;
	else
		mlx_delete_texture(tex);
}

void	load_bonus_texture(mlx_texture_t *tex, t_level *lvl, int type)
{
	if (type >= DOOR1 && type <= DOOR7)
		load_door_texture(tex, lvl, type);
	else if (type >= EXIT1 && type <= EXIT7)
		load_exit_texture(tex, lvl, type);
	else if (type == MONSTER)
		load_monster_texture(tex, lvl, type);
}
