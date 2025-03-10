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

static bool	init_window(t_data *data)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	data->mlx = mlx_init(W_WIDTH, W_HEIGHT, TITLE, false);
	if (!data->mlx)
		return (false);
	game_tick();
	input_tick();
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (print_error(FILE_NO_ARGS, false));
	ft_memset(&data, 0, sizeof(t_data));
	if (!init_window(&data))
		return (EXIT_FAILURE);
	if (!parse_data(argv, &data))
	{
		terminate(&data);
		return (EXIT_FAILURE);
	}
	mlx_key_hook(data.mlx, key_hook, &data);
	mlx_loop_hook(data.mlx, game_hook, &data);
	mlx_loop(data.mlx);
	terminate(&data);
	return (EXIT_SUCCESS);
}
