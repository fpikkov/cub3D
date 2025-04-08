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

static void	delete_image(mlx_t *mlx, mlx_image_t *image)
{
	if (image && mlx)
	{
		mlx_delete_image(mlx, image);
		image = NULL;
	}
}

void	delete_level_images(t_level *lvl)
{
	if (!lvl)
		return ;
	delete_image(*lvl->mlx, lvl->imgs.bg);
	delete_image(*lvl->mlx, lvl->imgs.fg);
}

void	terminate(t_data *data)
{
	if (!data)
		return ;
	if (data->file.build == true && data->file.root)
	{
		free(data->file.root);
		data->file.root = NULL;
	}
	if (data->levels)
		delete_levels(data);
	delete_image(data->mlx, data->minimap.img);
	delete_image(data->mlx, data->torch.dark);
	delete_image(data->mlx, data->torch.light);
	if (data->mlx)
		mlx_terminate(data->mlx);
}
