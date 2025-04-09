/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:34:12 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/03 13:34:13 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static bool	check_ext(char **argv)
{
	char	*ext;
	int		idx;

	idx = 1;
	while (argv[idx])
	{
		ext = ft_strrchr(argv[idx], '.');
		if (!ext)
			return (false);
		if (ft_strncmp(ext, ".cub", 5))
			return (false);
		idx++;
	}
	return (true);
}

static void	print_latest_map(t_data *data)
{
	t_level	*lvl;
	size_t	x;
	size_t	y;

	lvl = data->levels;
	while (lvl->next)
		lvl = lvl->next;
	y = 0;
	while (lvl->map[y])
	{
		x = 0;
		while (lvl->map[y][x])
		{
			if (lvl->map[y][x] == '1')
				ft_putchar_fd('#', STDOUT_FILENO);
			else
				ft_putchar_fd(' ', STDOUT_FILENO);
			x++;
		}
		ft_putendl_fd("!", STDOUT_FILENO);
		y++;
	}
	ft_putendl_fd("!", STDOUT_FILENO);
}

/**
 * @brief Parses data given in as program argument.
 * @param data struct to game data passed in by pointer to the struct
 * @return true if successfull, otherwise false
 */
bool	parse_data(char **argv, t_data *data)
{
	int	idx;

	if (!check_ext(argv))
		return (print_error(FILE_INVALID_EXTENSION, false));
	idx = 1;
	while (argv[idx])
	{
		if (!new_level_node(data))
			return (false);
		if (!parse_map(argv[idx], data))
			return (false);
		if (!validate_map(data))
			return (false);
		if (!parse_textures(argv[idx], data))
			return (false);
		if (DEBUG)
			print_latest_map(data);
		idx++;
	}
	if (!init_minimap(data))
		return (false);
	if (!create_screen_images(data))
		return (false);
	return (true);
}
