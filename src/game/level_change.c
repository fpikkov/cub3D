/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:17:31 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/10 12:17:32 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Initializes player position and rotation based on level data
 */
void	init_level_params(t_level *level, t_player *player)
{
	player->x = (double)level->player_x + 0.5;
	player->y = (double)level->player_y + 0.5;
	if (level->direction == 'N')
		player->angle = PI / 2.0;
	else if (level->direction == 'E')
		player->angle = 0;
	else if (level->direction == 'S')
		player->angle = (3.0 * PI) / 2.0;
	else if (level->direction == 'W')
		player->angle = PI;
	player->delta_x = cos(player->angle) * TRIG_MULTIPLIER;
	player->delta_y = sin(player->angle) * TRIG_MULTIPLIER;
}
