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

static char	*g_default_levels[4] = {
	"./build/cub3d",
	"maps/default.cub",
	"maps/level_one.cub"
};

bool	launch_parser(char **argv, t_data *data)
{
	if (!ft_strncmp(argv[1], "--launch", 9))
	{
		if (ft_strncmp(argv[0], g_default_levels[0], 14))
		{
			terminate(data);
			return (print_error(LAUNCH_PATH, true));
		}
		if (!parse_data(g_default_levels, data))
		{
			terminate(data);
			return (false);
		}
	}
	else
	{
		if (!parse_data(argv, data))
		{
			terminate(data);
			return (false);
		}
	}
	return (true);
}
