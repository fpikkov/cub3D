/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:42:46 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/05 16:42:48 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Frees a char pointer to pointer. This is called from delete_levels
 * so each map for a level gets freed u properly
 */
void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

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

void	terminate(t_data *data)
{
	if (!data)
		return ;
	if (data->levels)
		delete_levels(data);
	if (data->minimap.img)
		mlx_delete_image(data->mlx, data->minimap.img);
	if (data->torch.dark)
		mlx_delete_image(data->mlx, data->torch.dark);
	if (data->torch.light)
		mlx_delete_image(data->mlx, data->torch.light);
	if (data->mlx)
		mlx_terminate(data->mlx);
}
