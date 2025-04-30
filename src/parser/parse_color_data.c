/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:48:00 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/30 13:48:05 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static bool	is_texture_or_color(char *buffer, int idx, t_level *lvl)
{
	if (ft_strncmp(buffer + idx, "NO", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, NORTH));
	else if (ft_strncmp(buffer + idx, "EA", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, EAST));
	else if (ft_strncmp(buffer + idx, "SO", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, SOUTH));
	else if (ft_strncmp(buffer + idx, "WE", 2) == 0)
		return (load_texture(buffer + idx + 2, lvl, WEST));
	else if (ft_strncmp(buffer + idx, "F", 1) == 0)
		lvl->imgs.floor = fetch_color(buffer + idx + 1);
	else if (ft_strncmp(buffer + idx, "C", 1) == 0)
		lvl->imgs.ceiling = fetch_color(buffer + idx + 1);
	else if (is_bonus_texture(buffer + idx))
		return (load_bonus_texture(buffer + idx, lvl));
	else
	{
		print_error(UNKNOWN_TOKEN, false);
		return (false);
	}
	return (true);
}

/**
 * @brief Processes the fields from the given map file, ten either creates
 * textures or saves ceiling and floor colors.
 * @param[in] fd the file descriptor where to read from
 * @param[in] lvl the level for which the textures get fetched
 * @return STOP which means the EOF was reached. CONT if there are lines
 * left to read. CRITICAL when an error occured.
 */
int	parse_color_data(int fd, t_level *lvl)
{
	char	*buffer;
	int		idx;

	buffer = get_next_line(fd);
	if (buffer == NULL)
		return (STOP);
	idx = 0;
	while (buffer[idx] && ft_strchr(SEPARATOR, buffer[idx]) != NULL)
		idx++;
	if (buffer[idx] && buffer[idx] != '#')
	{
		if (map_started(buffer))
		{
			free(buffer);
			return (STOP);
		}
		if (!is_texture_or_color(buffer, idx, lvl))
		{
			free(buffer);
			return (CRITICAL);
		}
	}
	free(buffer);
	return (CONT);
}
