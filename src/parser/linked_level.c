/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_level.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:41:32 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/05 15:41:34 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Deletes all textures in a single level struct
 */
static void	delete_textures(t_level *lvl)
{
	if (lvl->textures.north)
	{
		mlx_delete_texture(lvl->textures.north);
		lvl->textures.north = NULL;
	}
	if (lvl->textures.east)
	{
		mlx_delete_texture(lvl->textures.east);
		lvl->textures.east = NULL;
	}
	if (lvl->textures.south)
	{
		mlx_delete_texture(lvl->textures.south);
		lvl->textures.south = NULL;
	}
	if (lvl->textures.west)
	{
		mlx_delete_texture(lvl->textures.west);
		lvl->textures.west = NULL;
	}
}

/**
 * @brief Deletes the image data and frees up maps in all level nodes
 * @param data the master struct of the project
 */
void	delete_levels(t_data *data)
{
	t_level	*ptr;
	t_level	*nptr;

	if (!data->levels)
		return ;
	ptr = data->levels;
	while (ptr)
	{
		nptr = ptr->next;
		delete_images(ptr, true);
		delete_textures(ptr);
		if (ptr->map)
			free_map(ptr->map);
		if (ptr->map_copy)
			free_map(ptr->map_copy);
		free(ptr);
		ptr = nptr;
	}
	data->levels = NULL;
}

static t_level	*init_level_node(t_data *data)
{
	static size_t	idx = 0;
	t_level			*new;

	new = (t_level *)ft_calloc(1, sizeof(t_level));
	if (!new)
		return ((void *)print_error(SYS_MALLOC, false));
	new->index = idx;
	idx++;
	new->mlx = &data->mlx;
	return (new);
}

/**
 * @brief Allocates a new level node in t_data
 * @return true on success, otherwise false
 */
bool	new_level_node(t_data *data)
{
	t_level	*ptr;

	if (!data->levels)
	{
		data->levels = init_level_node(data);
		if (!data->levels)
			return (false);
	}
	else
	{
		ptr = data->levels;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = init_level_node(data);
		if (!ptr->next)
			return (false);
	}
	return (true);
}
