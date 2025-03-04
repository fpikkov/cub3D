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

static bool	store_as_image(mlx_texture_t *tex, mlx_image_t **loc, t_data *data)
{
	if (*loc)
		print_error(TEXTURE_DUPLICATE, true, false);
	else
		*loc = mlx_texture_to_image(data->mlx, tex);
	if (!*loc)
	{
		print_error(TEXTURE_FAILURE, false, false);
		return (false);
	}
	return (true);
}

static bool	load_texture(char *buffer, t_data *data, int direction)
{
	mlx_texture_t	*texture;
	int				idx;
	bool			ret;

	idx = 0;
	while (buffer[idx] && ft_strchr(SEPARATOR, buffer[idx]) == NULL)
		idx++;
	if (!buffer[idx])
		return (true);
	texture = mlx_load_png(buffer + idx);
	if (!texture)
	{
		print_error(TEXTURE_NO_OPEN, true, false);
		return (false);
	}
	if (direction == NORTH)
		ret = store_as_image(texture, &data->imgs.north, data);
	else if (direction == EAST)
		ret = store_as_image(texture, &data->imgs.east, data);
	else if (direction == SOUTH)
		ret = store_as_image(texture, &data->imgs.south, data);
	else if (direction == WEST)
		ret = store_as_image(texture, &data->imgs.west, data);
	mlx_delete_texture(texture);
	return (ret);
}

/**
 * NOTE: Could be improved by creating a separate argument to uint8 converter
 */
static bool	load_color(char *buffer, t_color *loc)
{
	int		idx;

	if (!loc)
		return (false);
	idx = 0;
	while (buffer[idx] && ft_strchr(SEPARATOR, buffer[idx]) == NULL)
		idx++;
	loc->s_col.red = ft_atoi(buffer + idx);
	while (buffer[idx] && ft_strchr(NUMBERS, buffer[idx]) != NULL)
		idx++;
	while (buffer[idx] && ft_strchr(VALUE_SEPARATOR, buffer[idx]) != NULL)
		idx++;
	loc->s_col.green = ft_atoi(buffer + idx);
	while (buffer[idx] && ft_strchr(NUMBERS, buffer[idx]) != NULL)
		idx++;
	while (buffer[idx] && ft_strchr(VALUE_SEPARATOR, buffer[idx]) != NULL)
		idx++;
	loc->s_col.blue = ft_atoi(buffer + idx);
	while (buffer[idx] && ft_strchr(NUMBERS, buffer[idx]) != NULL)
		idx++;
	while (buffer[idx] && ft_strchr(VALUE_SEPARATOR, buffer[idx]) != NULL)
		idx++;
	if (buffer[idx])
		loc->s_col.alpha = ft_atoi(buffer + idx);
	return (true);
}

static bool	is_texture_or_color(char *buffer, int idx, t_data *data)
{
	if (ft_strncmp(buffer + idx, "NO", 2) == 0)
		return (load_texture(buffer + idx + 2, data, NORTH));
	else if (ft_strncmp(buffer + idx, "EA", 2) == 0)
		return (load_texture(buffer + idx + 2, data, EAST));
	else if (ft_strncmp(buffer + idx, "SO", 2) == 0)
		return (load_texture(buffer + idx + 2, data, SOUTH));
	else if (ft_strncmp(buffer + idx, "WE", 2) == 0)
		return (load_texture(buffer + idx + 2, data, WEST));
	else if (ft_strncmp(buffer + idx, "F", 1) == 0)
		return (load_color(buffer + idx + 1, &data->imgs.floor));
	else if (ft_strncmp(buffer + idx, "C", 1) == 0)
		return (load_color(buffer + idx + 1, &data->imgs.ceiling));
	return (true);
}

/**
 * @brief Processes the fields from the given map file, ten either creates
 * textures or saves ceiling and floor colors.
 * @param[in] fd the file descriptor where to read from
 * @param[in] data the master struct of the project
 * @return STOP which means the EOF was reached. CONT if there are lines
 * left to read. CRITICAL when an error occured.
 */
int	parse_color_data(int fd, t_data *data)
{
	char	*buffer;
	int		idx;

	buffer = get_next_line(fd);
	if (buffer == NULL)
		return (STOP);
	idx = 0;
	while (buffer[idx] && ft_strchr(SEPARATOR, buffer[idx]) == NULL)
		idx++;
	if (buffer[idx] != NULL && buffer[idx] != '#')
	{
		if (!is_texture_or_color(buffer, idx, data))
		{
			free(buffer);
			return (CRITICAL);
		}
	}
	free(buffer);
	return (CONT);
}
