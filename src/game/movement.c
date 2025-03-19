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

// TODO: Collision checking
void	move_forward(t_player *p)
{
	p->x += cos(p->angle) * MOVE_SPEED;
	p->y += sin(p->angle) * MOVE_SPEED;
}

// TODO: Collision checking
void	move_backward(t_player *p)
{
	p->x -= cos(p->angle) * MOVE_SPEED;
	p->y -= sin(p->angle) * MOVE_SPEED;
}

// TODO: Collision checking
// TODO: Double check the math
void	move_left(t_player *p)
{
	double	side_delta;

	side_delta = p->angle - PI2;
	if (side_delta < 0)
		side_delta += PI * 2.0;
	p->x += cos(side_delta) * MOVE_SPEED;
	p->y -= sin(side_delta) * MOVE_SPEED;
}

// TODO: Collision checking
// TODO: Double check the math
void	move_right(t_player *p)
{
	double	side_delta;

	side_delta = p->angle + PI2;
	if (side_delta > PI * 2.0)
		side_delta -= PI * 2.0;
	p->x += cos(side_delta) * MOVE_SPEED;
	p->y -= sin(side_delta) * MOVE_SPEED;
}
