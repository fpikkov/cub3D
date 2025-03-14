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
	if (all && lvl->imgs.bg)
	{
		mlx_delete_image(*lvl->mlx, lvl->imgs.bg);
		lvl->imgs.bg = NULL;
	}
	if (all && lvl->imgs.fg)
	{
		mlx_delete_image(*lvl->mlx, lvl->imgs.fg);
		lvl->imgs.fg = NULL;
	}
}

void	new_images(t_level *lvl)
{
	if (!lvl)
		return ;
	delete_images(lvl, false);
	reset_foreground(lvl);
	lvl->imgs.north = mlx_texture_to_image(*lvl->mlx, lvl->textures.north);
	lvl->imgs.east = mlx_texture_to_image(*lvl->mlx, lvl->textures.east);
	lvl->imgs.south = mlx_texture_to_image(*lvl->mlx, lvl->textures.south);
	lvl->imgs.west = mlx_texture_to_image(*lvl->mlx, lvl->textures.west);
	if (!lvl->imgs.north || !lvl->imgs.east || \
	!lvl->imgs.south || !lvl->imgs.west)
		print_error(IMG_FAILURE, true);
}

void	reset_foreground(t_level *lvl)
{
	ft_memset(lvl->imgs.fg->pixels, 0, \
	lvl->imgs.fg->width * lvl->imgs.fg->height * sizeof(int32_t));
}
