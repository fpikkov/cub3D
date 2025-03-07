/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:21:34 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/07 16:21:35 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	delete_walls(t_level *lvl)
{
	if (lvl->imgs.north)
	{
		mlx_delete_image(*lvl->mlx, lvl->imgs.north);
		lvl->imgs.north = NULL;
	}
	if (lvl->imgs.east)
	{
		mlx_delete_image(*lvl->mlx, lvl->imgs.east);
		lvl->imgs.east = NULL;
	}
	if (lvl->imgs.south)
	{
		mlx_delete_image(*lvl->mlx, lvl->imgs.south);
		lvl->imgs.south = NULL;
	}
	if (lvl->imgs.west)
	{
		mlx_delete_image(*lvl->mlx, lvl->imgs.west);
		lvl->imgs.west = NULL;
	}
}

void	delete_images(t_level *lvl, bool all)
{
	if (!lvl)
		return ;
	delete_walls(lvl);
	if (all)
	{
		if (lvl->imgs.floor)
			mlx_delete_image(*lvl->mlx, lvl->imgs.floor);
		if (lvl->imgs.ceiling)
			mlx_delete_image(*lvl->mlx, lvl->imgs.ceiling);
	}
}

void	new_images(t_level *lvl)
{
	if (!lvl)
		return ;
	delete_images(lvl, false);
	lvl->imgs.north = mlx_texture_to_image(*lvl->mlx, lvl->textures.north);
	lvl->imgs.east = mlx_texture_to_image(*lvl->mlx, lvl->textures.east);
	lvl->imgs.south = mlx_texture_to_image(*lvl->mlx, lvl->textures.south);
	lvl->imgs.west = mlx_texture_to_image(*lvl->mlx, lvl->textures.west);
	if (!lvl->imgs.north || !lvl->imgs.east || \
	!lvl->imgs.south || !lvl->imgs.west)
		print_error(IMG_FAILURE, true);
}
