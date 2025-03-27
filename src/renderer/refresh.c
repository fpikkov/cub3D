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

void	delete_level_images(t_level *lvl)
{
	if (!lvl)
		return ;
	if (lvl->imgs.bg)
	{
		mlx_delete_image(*lvl->mlx, lvl->imgs.bg);
		lvl->imgs.bg = NULL;
	}
	if (lvl->imgs.fg)
	{
		mlx_delete_image(*lvl->mlx, lvl->imgs.fg);
		lvl->imgs.fg = NULL;
	}
}

void	reset_foreground(t_level *lvl)
{
	if (lvl->imgs.fg)
	{
		ft_memset(lvl->imgs.fg->pixels, 0, \
		lvl->imgs.fg->width * lvl->imgs.fg->height * sizeof(int32_t));
	}
}
