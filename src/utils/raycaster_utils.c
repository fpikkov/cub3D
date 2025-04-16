/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:48:46 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/16 13:48:50 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	step_vertical(t_ray *r)
{
	r->side_dist_x += r->delta_dist_x;
	r->map_x += r->step_x;
	r->side = VERTICAL;
}

void	step_horizontal(t_ray *r)
{
	r->side_dist_y += r->delta_dist_y;
	r->map_y += r->step_y;
	r->side = HORIZONTAL;
}
