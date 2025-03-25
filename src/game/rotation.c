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

void	rotate_left(t_player *p)
{
	p->angle -= ROTATE_AMOUNT;
	if (p->angle < 0)
		p->angle += PI * 2.0;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
}

void	rotate_right(t_player *p)
{
	p->angle += ROTATE_AMOUNT;
	if (p->angle > PI * 2.0)
		p->angle -= PI * 2.0;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
}
