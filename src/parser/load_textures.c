/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:45:46 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/30 13:45:52 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	load_texture(char *buffer, t_level *lvl, int direction)
{
	mlx_texture_t	*texture;
	char			*path;

	if (!buffer)
		return (true);
	path = texture_path(buffer, &lvl->data->file);
	if (!path)
		return (false);
	texture = mlx_load_png(path);
	free(path);
	if (!texture)
		return (print_error(TEXTURE_NO_OPEN, false));
	if (direction == NORTH)
		return (save_texture(&lvl->textures.north, texture));
	else if (direction == EAST)
		return (save_texture(&lvl->textures.east, texture));
	else if (direction == SOUTH)
		return (save_texture(&lvl->textures.south, texture));
	else if (direction == WEST)
		return (save_texture(&lvl->textures.west, texture));
	return (true);
}

bool	load_bonus_texture(char *buffer, t_level *lvl)
{
	mlx_texture_t	*texture;
	int				type;
	char			*path;

	if (!buffer)
		return (true);
	path = texture_path(buffer + 2, &lvl->data->file);
	if (!path)
		return (false);
	texture = mlx_load_png(path);
	free(path);
	if (!texture)
		return (print_error(TEXTURE_NO_OPEN, false));
	type = pick_bonus_texture(buffer);
	return (save_bonus_texture(texture, lvl, type));
}
