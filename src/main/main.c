/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:49:54 by fpikkov           #+#    #+#             */
/*   Updated: 2025/02/28 12:49:57 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// TODO: Temporary function for debugging, remove or refactor later
static bool	init_window(t_data *data)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, false);
	if (!data->mlx)
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (!init_window(&data))
		return (EXIT_FAILURE);
	if (!parse_data(argc, argv, &data))
	{
		cube_terminate(&data);
		return (EXIT_FAILURE);
	}
	cube_terminate(&data);
	return (EXIT_SUCCESS);
}
