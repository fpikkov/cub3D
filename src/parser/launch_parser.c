/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:55:51 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/27 13:55:52 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	*g_default_levels[5] = {
	"./build/cub3d",
	"maps/default.cub",
	"maps/level_one.cub",
	"maps/level_three.cub"
};

static void	argument_failure(char **args, size_t idx)
{
	while (idx > 0)
	{
		if (args[idx])
			free(args[idx]);
		args[idx] = NULL;
		idx--;
	}
	if (args[idx])
		free(args[idx]);
	args[idx] = NULL;
	if (args)
		free(args);
	args = NULL;
}

static char	**construct_launch_args(t_data *data)
{
	char	**args;
	size_t	count;
	size_t	idx;

	args = NULL;
	count = map_row_len(g_default_levels);
	args = ft_calloc(count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(g_default_levels[0]);
	idx = 1;
	while (idx < count)
	{
		args[idx] = ft_strjoin(data->file.root, g_default_levels[idx]);
		if (!args[idx])
		{
			argument_failure(args, idx - 1);
			return (NULL);
		}
		idx++;
	}
	return (args);
}

bool	launch_parser(char **argv, t_data *data)
{
	char	**args;

	args = argv;
	if (build_path(argv[0], data) == CRITICAL)
		return (print_error(PATH_FAILURE, false));
	if (!ft_strncmp(argv[1], "--launch", 9))
	{
		if (!data->file.build)
			args = g_default_levels;
		else
			args = construct_launch_args(data);
	}
	if (!parse_data(args, data))
	{
		terminate(data);
		return (false);
	}
	return (true);
}
