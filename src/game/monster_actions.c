/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:42:54 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/09 09:42:58 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	void	decide_dir(t_monster *monster, int player_x, int player_y)
{
	if (monster->y < player_y)
		monster->move_down = true;
	else if (monster->y > player_y)
		monster->move_up = true;
	if (monster->x < player_x)
		monster->move_right = true;
	else if (monster->x > player_x)
		monster->move_left = true;
}

static	void	move_monster(t_level *lvl, t_monster *monster)
{
	lvl->map[monster->y][monster->x] = '0';
	if (monster->move_down && !is_wall(lvl, monster->x, monster->y + 1)
		&& !get_door_type(lvl, monster->x, monster->y + 1))
		monster->y++;
	else if (monster->move_up && !is_wall(lvl, monster->x, monster->y - 1)
		&& !get_door_type(lvl, monster->x, monster->y - 1))
		monster->y--;
	if (monster->move_right && !is_wall(lvl, monster->x + 1, monster->y)
		&& !get_door_type(lvl, monster->x + 1, monster->y))
		monster->x++;
	else if (monster->move_left && !is_wall(lvl, monster->x - 1, monster->y)
		&& !get_door_type(lvl, monster->x - 1, monster->y))
		monster->x--;
	lvl->map[monster->y][monster->x] = 'M';
	monster->move_down = false;
	monster->move_up = false;
	monster->move_right = false;
	monster->move_left = false;
}

static	bool	player_caught(t_monster *monster, int player_x, int player_y)
{
	if (monster->x == player_x && monster->y == player_y)
		return (true);
	return (false);
}

void	monster_action(t_level *lvl)
{
	int		id;

	if (!lvl->has_monsters)
		return ;
	id = 0;
	while (id < lvl->monster_count)
	{
		if (lvl->monster[id].active \
		&& get_time () - lvl->monster[id].time > 2000)
		{
			decide_dir(&lvl->monster[id], lvl->player_x, lvl->player_y);
			move_monster(lvl, &lvl->monster[id]);
			if (player_caught(&lvl->monster[id], lvl->player_x, lvl->player_y))
				lvl->player_dead = true;
			lvl->monster[id].time = get_time();
		}
		lvl->monster[id].active = true;
		id++;
	}
}
