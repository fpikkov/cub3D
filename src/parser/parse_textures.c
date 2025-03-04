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
 * @return false if a critial error occured
 */
bool	parse_textures(char *filename, t_data *data)
{
	int	fd;
	int	ret;

	ret = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(FILE_NO_OPEN, false, false);
		return (false);
	}
	while (true)
	{
		ret = parse_color_data(fd, data);
		if (ret == STOP || ret == CRITICAL)
			break ;
	}
	close(fd);
	if (ret == CRITICAL)
		return (false);
	return (true);
}
