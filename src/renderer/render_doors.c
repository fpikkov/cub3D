/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:38 by ahentton          #+#    #+#             */
/*   Updated: 2025/04/11 10:27:43 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	mlx_texture_t	*pick_exit_texture(t_level *lvl, int status)
{
	if (status == CLOSED)
		return (lvl->textures.exit1);
	else if (status == OPENING1)
		return (lvl->textures.exit2);
	else if (status == OPENING2)
		return (lvl->textures.exit3);
	else if (status == OPENING3)
		return (lvl->textures.exit4);
	else if (status == OPENING4)
		return (lvl->textures.exit5);
	else if (status == OPENING5)
		return (lvl->textures.exit6);
	else if (status == OPEN)
		return (lvl->textures.exit7);
	return (NULL);
}

static uint32_t	pick_door_texture(t_door_data *door, t_level *lvl, int y)
{
	uint32_t		color;
	mlx_texture_t	*tex;

	color = 0x0;
	if (lvl->map[door->y][door->x] == '2')
		color = nearest_neighbor(lvl->textures.door1, door->hit_column, y);
	else if (lvl->map[door->y][door->x] == '3')
		color = nearest_neighbor(lvl->textures.door2, door->hit_column, y);
	else if (lvl->map[door->y][door->x] == '4')
		color = nearest_neighbor(lvl->textures.door3, door->hit_column, y);
	else if (lvl->map[door->y][door->x] == '5')
		color = nearest_neighbor(lvl->textures.door4, door->hit_column, y);
	else if (lvl->map[door->y][door->x] == '6')
		color = nearest_neighbor(lvl->textures.door5, door->hit_column, y);
	else if (lvl->map[door->y][door->x] == '7')
		color = nearest_neighbor(lvl->textures.door6, door->hit_column, y);
	else if (lvl->map[door->y][door->x] == '8')
		color = nearest_neighbor(lvl->textures.door7, door->hit_column, y);
	else if (lvl->map[door->y][door->x] == 'P')
	{
		tex = pick_exit_texture(lvl, lvl->exit.status);
		color = nearest_neighbor(tex, door->hit_column, y);
		tex = NULL;
	}
	return (color);
}

void	draw_doors(t_ray *ray, t_level *lvl, int x)
{
	t_line		line;
	int			scaled_y;
	uint32_t	color;

	color = 0;
	while (--ray->door_count >= 0)
	{
		ft_memset(&line, 0, sizeof(t_line));
		line_init(&line, ray->doors[ray->door_count].dist);
		if (line.current < 0)
			line.current = 0;
		while (line.current <= line.end && line.current < W_HEIGHT)
		{
			scaled_y = scale_texture_height(&line);
			color = pick_door_texture(&ray->doors[ray->door_count], \
			lvl, scaled_y);
			if (color)
			{
				mlx_put_pixel(lvl->imgs.fg, x, (int)line.current, color);
				draw_light(lvl, &line, x, \
				ray->doors[ray->door_count].dist);
			}
			line.current++;
		}
	}
}
