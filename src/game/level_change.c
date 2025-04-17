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
	player->x = level->player_x + 0.5;
	player->y = level->player_y + 0.5;
	if (level->direction == 'N')
		player->angle = UP;
	else if (level->direction == 'E')
		player->angle = RIGHT;
	else if (level->direction == 'S')
		player->angle = DOWN;
	else if (level->direction == 'W')
		player->angle = LEFT;
	player->dir_x = cosf(player->angle);
	player->dir_y = sinf(player->angle);
	player->right_x = cosf(player->angle + PI_DIAGONAL);
	player->right_y = sinf(player->angle + PI_DIAGONAL);
}

/**
 * @brief Renders the floor and ceiling and initializes player position.
 * This function will initialize the loading of a new level.
 */
void	level_setup(t_level *lvl, t_player *p)
{
	if (lvl->loaded == false)
	{
		init_level_params(lvl, p);
		if (lvl->imgs.bg)
		{
			mlx_image_to_window(*lvl->mlx, lvl->imgs.bg, 0, 0);
			mlx_set_instance_depth(lvl->imgs.bg->instances, BG_DEPTH);
		}
		if (lvl->imgs.fg)
		{
			mlx_image_to_window(*lvl->mlx, lvl->imgs.fg, 0, 0);
			mlx_set_instance_depth(lvl->imgs.fg->instances, FG_DEPTH);
		}
		lvl->loaded = true;
	}
}

/**
 * @brief Fetches currently loaded level from data
 * @return instance of the currently loaded level
 */
t_level	*current_level(t_data *data)
{
	t_level	*instance;

	instance = data->levels;
	while (instance->index != data->lvl_idx && instance->next)
		instance = instance->next;
	return (instance);
}

/**
 * @brief Quits the game if no next level exists, otherwise
 * will increase the current level index in data and delete previous
 * level's foreground and background images.
 */
void	next_level(t_data *data)
{
	t_level	*previous;

	previous = current_level(data);
	if (!previous->next)
		mlx_close_window(data->mlx);
	else
	{
		data->lvl_idx++;
		delete_level_images(previous);
	}
}
