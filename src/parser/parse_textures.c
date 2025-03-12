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
	if (!create_background(lvl))
		return (false);
	return (true);
}
