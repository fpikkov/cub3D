/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:48:59 by fpikkov           #+#    #+#             */
/*   Updated: 2025/02/28 12:49:00 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "headers.h"
# include "types.h"
# include "constants.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

// Parsing functions

bool		parse_data(char **argv, t_data *data);
bool		parse_textures(char *filename, t_data *data);
int			parse_color_data(int fd, t_level *lvl);
uint32_t	fetch_color(char *buffer);
bool		create_background(t_level *lvl);
bool		create_foreground(t_level *lvl);
bool		new_level_node(t_data *data);

bool		parse_map(char *filename, t_data *data);
char		**extract_map(char *file);
bool		validate_map(t_data *data);
int			map_col_len(char **map);
int			map_row_len(char **map);
char		**resize_to_rectangular(char **map);

// Utility functions

double		to_radian(int degrees);
void		space_to_one(char **map);
bool		print_error(t_errors error, bool warning);

// Game logic

void		key_hook(mlx_key_data_t keydata, void *param);
void		game_hook(void *param);
bool		game_tick(void);
bool		input_tick(void);
void		init_level_params(t_level *level, t_player *player);

// Renderer

void		new_images(t_level *lvl);
void		delete_images(t_level *lvl, bool all);
void		reset_foreground(t_level *lvl);
void		render_surfaces(t_level *lvl, t_player *p);
double		raycast(t_ray *ray, t_level *lvl, t_player *p, int x);
uint32_t	nearest_neighbor(mlx_texture_t *tex, uint32_t x, uint32_t y);

// Player position

void		move_forward(t_player *p);
void		move_backward(t_player *p);
void		move_left(t_player *p);
void		move_right(t_player *p);
void		rotate_left(t_player *p);
void		rotate_right(t_player *p);

// Cleanup functions

void		free_map(char **map);
void		delete_levels(t_data *data);
void		terminate(t_data *data);

#endif
