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

bool	verify_png(char *filepath)
{
	char	*ext;

	ext = ft_strrchr(filepath, '.');
	if (!ext)
		return (false);
	if (ft_strncmp(ext, ".png", 5))
		return (false);
	return (true);
}

char	*texture_path(char *buffer, t_file *info)
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
	path = tex_join_path(buffer, start, end - start, info);
	if (!path)
		return ((void *)print_error(SYS_MALLOC, false));
	if (!verify_png(path))
	{
		free(path);
		return ((void *)print_error(TEXTURE_NO_PNG, false));
	}
	return (path);
}

bool	save_texture(mlx_texture_t **texture, mlx_texture_t *new)
{
	if (!*texture)
		*texture = new;
	else
	{
		mlx_delete_texture(new);
		print_error(TEXTURE_DUPLICATE, false);
		return (false);
	}
	return (true);
}

bool	map_started(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (!strchr(" 01", buffer[i]))
			return (false);
		i++;
	}
	return (true);
}
