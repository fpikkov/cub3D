/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:08:29 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/10 12:08:31 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	rotate_left(t_player *p, float delay)
{
	p->angle -= ROTATE_AMOUNT * delay;
	if (p->angle < 0)
		p->angle += PI * 2.0;
	p->dir_x = cosf(p->angle);
	p->dir_y = sinf(p->angle);
	p->right_x = cosf(p->angle + PI_DIAGONAL);
	p->right_y = sinf(p->angle + PI_DIAGONAL);
}

static void	rotate_right(t_player *p, float delay)
{
	p->angle += ROTATE_AMOUNT * delay;
	if (p->angle > PI * 2.0)
		p->angle -= PI * 2.0;
	p->dir_x = cosf(p->angle);
	p->dir_y = sinf(p->angle);
	p->right_x = cosf(p->angle + PI_DIAGONAL);
	p->right_y = sinf(p->angle + PI_DIAGONAL);
}

void	rotation_handler(t_data *data, float delay)
{
	int	mouse_x;
	int	mouse_y;

	mouse_x = 0;
	mouse_y = 0;
	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
	mouse_x -= W_WIDTH / 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mouse_x + DPI < 0)
		rotate_left(&data->player, delay);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) || mouse_x - DPI > 0)
		rotate_right(&data->player, delay);
	mlx_set_mouse_pos(data->mlx, W_WIDTH / 2, W_HEIGHT / 2);
}
