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
	return (true);
}

static void	init_mouse(t_data *data)
{
	mlx_set_mouse_pos(data->mlx, W_WIDTH / 2, W_HEIGHT / 2);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_mouse_hook(data->mlx, mouse_hook, data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (print_error(FILE_NO_ARGS, false));
	ft_memset(&data, 0, sizeof(t_data));
	if (!init_window(&data))
		return (EXIT_FAILURE);
	if (!launch_parser(argv, &data))
		return (EXIT_FAILURE);
	ft_memset(&data.levels->door, 0, sizeof(t_door));
	mlx_key_hook(data.mlx, key_hook, &data);
	init_mouse(&data);
	mlx_loop_hook(data.mlx, game_hook, &data);
	mlx_loop(data.mlx);
	terminate(&data);
	return (EXIT_SUCCESS);
}
