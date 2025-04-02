/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:29:28 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/14 16:29:29 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

float	to_radian(int degrees)
{
	return ((float)(degrees * DEGREE));
}

int	pack_shorts(uint16_t x, uint16_t y)
{
	int	package;

	package = 0;
	package |= x << 16;
	package |= y;
	return (package);
}

void	unpack_shorts(int *x, int *y, int package)
{
	*x = (package >> 16) & 0xFFFF;
	*y = package & 0xFFFF;
}
