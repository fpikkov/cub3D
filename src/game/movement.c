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

void	move_forward(t_player *p)
{
	p->x += p->delta_x;
	p->y += p->delta_y;
}

void	move_backward(t_player *p)
{
	p->x -= p->delta_x;
	p->y -= p->delta_y;
}

// Double check the math
void	move_left(t_player *p)
{
	p->x -= p->delta_x;
	p->y += p->delta_y;
}

// Double check the math.
void	move_right(t_player *p)
{
	p->x += p->delta_x;
	p->y -= p->delta_y;
}
