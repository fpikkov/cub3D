/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:58:57 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/04 15:58:59 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	bool	sprite_textures_exist(t_level *lvl)
{
	if (lvl->has_doors)
	{
		if (!lvl->textures.door1 || !lvl->textures.door2
			|| !lvl->textures.door3 || !lvl->textures.door4
			|| !lvl->textures.door5 || !lvl->textures.door6
			|| !lvl->textures.door7)
			return (false);
	}
	if (lvl->has_monsters)
	{
		if (!lvl->textures.monster)
			return (false);
	}
	if (lvl->has_exit)
	{
		if (!lvl->textures.exit1 || !lvl->textures.exit2
			|| !lvl->textures.exit3 || !lvl->textures.exit4
			|| !lvl->textures.exit5 || !lvl->textures.exit6
			|| !lvl->textures.exit7)
			return (false);
	}
	return (true);
}

static bool	textures_exist(t_level *lvl)
{
	if (!lvl->textures.north || !lvl->textures.south \
		|| !lvl->textures.east || !lvl->textures.west)
		return (print_error(FILE_MISSING_PARAMS, false));
	else if (!sprite_textures_exist(lvl))
		return (print_error(FILE_MISSING_PARAMS, false));
	return (true);
}

/**
 * @brief Reads color and texture information from file
 * @param filename the file which to read from
 * @param data struct which contains levels where textures get stored
 * @return false if a critial error occured
 */
bool	parse_textures(char *filename, t_data *data)
{
	t_level	*lvl;
	int		fd;
	int		ret;

	ret = 0;
	lvl = data->levels;
	while (lvl->next)
		lvl = lvl->next;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_error(FILE_NO_OPEN, false));
	while (true)
	{
		ret = parse_color_data(fd, lvl);
		if (ret == STOP || ret == CRITICAL)
			break ;
	}
	close(fd);
	if (ret == CRITICAL)
		return (false);
	if (!create_background(lvl) || !create_foreground(lvl) \
	|| !textures_exist(lvl))
		return (false);
	return (true);
}
