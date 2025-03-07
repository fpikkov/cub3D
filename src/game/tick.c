/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:56:24 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/07 12:56:26 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int64_t	get_time(void)
{
	struct timeval	tv;

	ft_memset(&tv, 0, sizeof(struct timeval));
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Checks whether the game should draw a new frame
 * @return true if it should, otherwise false
 */
bool	game_tick(void)
{
	static int64_t	current = 0;

	if (current == 0)
		current = get_time();
	if ((get_time() - current) >= MSEC_PER_FRAME)
	{
		current = get_time();
		return (true);
	}
	return (false);
}
