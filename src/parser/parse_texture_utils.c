/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:18:31 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/04 17:18:32 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static bool	verify_png(char *filepath)
{
	char	*ext;

	ext = ft_strrchr(filepath, '.');
	if (!ext)
		return (false);
	if (ft_strncmp(ext, ".png", 5))
		return (false);
	return (true);
}

static char	*texture_path(char *buffer)
{
	char	*path;
	size_t	start;
	size_t	end;

	if (!buffer)
		return (NULL);
	start = 0;
	while (buffer[start] && ft_strchr(SEPARATOR, buffer[start]) != NULL)
		start++;
	end = start;
	while (buffer[end] && ft_strchr(SEPARATOR, buffer[end]) == NULL)
		end++;
	path = ft_substr(buffer, start, end - start);
	if (!path)
		return ((void *)print_error(SYS_MALLOC, false));
	if (!verify_png(path))
	{
		free(path);
		return ((void *)print_error(TEXTURE_NO_PNG, false));
	}
	return (path);
}

bool	load_texture(char *buffer, t_level *lvl, int direction)
{
	mlx_texture_t	*texture;
	char			*path;

	if (!buffer)
		return (true);
	path = texture_path(buffer);
	if (!path)
		return (false);
	texture = mlx_load_png(path);
	free(path);
	if (!texture)
		return (print_error(TEXTURE_NO_OPEN, false));
	if (direction == NORTH && !lvl->textures.north)
		lvl->textures.north = texture;
	else if (direction == EAST && !lvl->textures.east)
		lvl->textures.east = texture;
	else if (direction == SOUTH && !lvl->textures.south)
		lvl->textures.south = texture;
	else if (direction == WEST && !lvl->textures.west)
		lvl->textures.west = texture;
	else if (direction >= DOOR1 && direction <= DOOR7)
		load_door_texture(texture, lvl, direction);
	else
		mlx_delete_texture(texture);
	return (true);
}

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
	else
		return (is_door_texture(buffer, idx, lvl));
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
		if (!is_texture_or_color(buffer, idx, lvl))
		{
			free(buffer);
			return (CRITICAL);
		}
	}
	free(buffer);
	return (CONT);
}
