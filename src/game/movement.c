/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:03:43 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/10 12:03:45 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	move_forward(t_player *p, t_level *lvl)
{
	if (!is_wall(lvl, p->x + (p->dir_x * (MOVE_SPEED + BOUNDARY)), p->y + (p->dir_y * MOVE_SPEED)))
		p->x += p->dir_x * MOVE_SPEED;
	if (!is_wall(lvl, p->x + (p->dir_x * MOVE_SPEED), p->y + (p->dir_y * (MOVE_SPEED + BOUNDARY))))
		p->y += p->dir_y * MOVE_SPEED;
}

void	move_backward(t_player *p, t_level *lvl)
{
	if (!is_wall(lvl, p->x - (p->dir_x * (MOVE_SPEED + BOUNDARY)), p->y - (p->dir_y * MOVE_SPEED)))
		p->x -= p->dir_x * MOVE_SPEED;
	if (!is_wall(lvl, p->x - (p->dir_x * MOVE_SPEED), p->y - (p->dir_y * (MOVE_SPEED + BOUNDARY))))
		p->y -= p->dir_y * MOVE_SPEED;
}

void	move_left(t_player *p, t_level *lvl)
{
	double	delta;
	double	dir_x;
	double	dir_y;

	delta = p->angle - PI_DIAGONAL;
	if (delta < 0)
		delta += PI2;
	dir_x = -cos(delta);
	dir_y = -sin(delta);
	if (is_wall(lvl, (int)(p->x - (dir_x * (MOVE_SPEED + BOUNDARY))), \
	(int)(p->y - (dir_y * (MOVE_SPEED + BOUNDARY)))))
		return ;
	p->x -= dir_x * MOVE_SPEED;
	p->y -= dir_y * MOVE_SPEED;
}

void	move_right(t_player *p, t_level *lvl)
{
	double	delta;
	double	dir_x;
	double	dir_y;

	delta = p->angle + PI_DIAGONAL;
	if (delta > PI2)
		delta -= PI2;
	dir_x = cos(delta);
	dir_y = sin(delta);
	if (is_wall(lvl, (int)(p->x + (dir_x * (MOVE_SPEED + BOUNDARY))), \
	(int)(p->y + (dir_y * (MOVE_SPEED + BOUNDARY)))))
		return ;
	p->x += dir_x * MOVE_SPEED;
	p->y += dir_y * MOVE_SPEED;
}
