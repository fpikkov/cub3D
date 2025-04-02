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

bool		launch_parser(char **argv, t_data *data);
bool		parse_data(char **argv, t_data *data);
bool		parse_textures(char *filename, t_data *data);
int			parse_color_data(int fd, t_level *lvl);
uint32_t	fetch_color(char *buffer);
bool		create_background(t_level *lvl);
bool		create_foreground(t_level *lvl);
bool		create_screen_images(t_data *data);
bool		new_level_node(t_data *data);

bool		parse_map(char *filename, t_data *data);
char		**extract_map(char *file);
bool		validate_map(t_data *data);
int			map_col_len(char **map);
int			map_row_len(char **map);
char		**resize_to_rectangular(char **map);

// Utility functions

float		to_radian(int degrees);
void		space_to_one(char **map);
bool		print_error(t_errors error, bool warning);
bool		is_wall(t_level	*lvl, int x, int y);
int			pack_shorts(uint16_t x, uint16_t y);
void		unpack_shorts(int *x, int *y, int package);

// Game logic

void		key_hook(mlx_key_data_t keydata, void *param);
void		mouse_hook(mouse_key_t b, action_t a, modifier_key_t m, void *p);
void		game_hook(void *param);
bool		game_tick(void);
float		frame_delay(void);
void		next_level(t_data *data);

// Level handling

void		init_level_params(t_level *level, t_player *player);
void		level_setup(t_level *lvl, t_player *p);
t_level		*current_level(t_data *data);

// Renderer

void		delete_level_images(t_level *lvl);
void		reset_foreground(t_level *lvl);
void		render_surfaces(t_level *lvl, t_player *p);
bool		raycast(t_ray *ray, t_level *lvl, t_player *p, int x);
uint32_t	nearest_neighbor(mlx_texture_t *tex, uint32_t x, uint32_t y);
void		image_fill(mlx_image_t *img, uint32_t color);

// Lighting

void		draw_light(t_level *lvl, t_line *line, int x, float distance);
void 		light_floor(t_level *lvl, t_line *line, int x, float distance);
uint32_t	light_level(uint32_t shade, uint32_t bright, int level);
int			attenuation_factor(int level, float distance);
int			light_step(int x, int size);

// Player position

void		movement_handler(t_data *data, t_level *lvl);
void		rotation_handler(t_data *data, float delay);

// Minimap

bool		init_minimap(t_data *data);
void		draw_minimap(t_minimap *map);
void		update_minimap(t_data *data, t_level *lvl);

// Cleanup functions

void		free_map(char **map);
void		delete_levels(t_data *data);
void		terminate(t_data *data);

#endif
