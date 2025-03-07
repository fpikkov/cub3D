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

static bool	store_as_image(mlx_texture_t *tex, mlx_image_t **loc, t_level *lvl)
{
	if (*loc)
		print_error(TEXTURE_DUPLICATE, true);
	else
		*loc = mlx_texture_to_image(*lvl->mlx, tex);
	if (!*loc)
		return (print_error(TEXTURE_FAILURE, false));
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
		return (NULL);
	return (path);
}

static bool	load_texture(char *buffer, t_level *lvl, int direction)
{
	mlx_texture_t	*texture;
	char			*path;
	bool			ret;

	if (!buffer)
		return (true);
	path = texture_path(buffer);
	if (!path)
		return (print_error(SYS_MALLOC, false));
	texture = mlx_load_png(path);
	free(path);
	if (!texture)
		return (print_error(TEXTURE_NO_OPEN, false));
	ret = true;
	if (direction == NORTH)
		ret = store_as_image(texture, &lvl->imgs.north, lvl);
	else if (direction == EAST)
		ret = store_as_image(texture, &lvl->imgs.east, lvl);
	else if (direction == SOUTH)
		ret = store_as_image(texture, &lvl->imgs.south, lvl);
	else if (direction == WEST)
		ret = store_as_image(texture, &lvl->imgs.west, lvl);
	mlx_delete_texture(texture);
	return (ret);
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
		return (load_color(buffer + idx + 1, lvl, FLOOR));
	else if (ft_strncmp(buffer + idx, "C", 1) == 0)
		return (load_color(buffer + idx + 1, lvl, CEILING));
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
