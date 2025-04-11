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
int			build_path(char *path, t_data *data);
bool		parse_data(char **argv, t_data *data);
bool		parse_textures(char *filename, t_data *data);
bool		is_sprite_texture(char *buffer, int idx, t_level *lvl);
bool		load_texture(char *buffer, t_level *lvl, int direction);
char		*tex_join_path(char *buf, size_t st, size_t len, t_file *info);
void		load_door_texture(mlx_texture_t *tex, t_level *lvl, int type);
void		load_exit_texture(mlx_texture_t *tex, t_level *lvl, int type);
void		load_monster_texture(mlx_texture_t *tex, t_level *lvl, int type);
int			parse_color_data(int fd, t_level *lvl);
uint32_t	fetch_color(char *buffer);
bool		create_background(t_level *lvl);
bool		create_foreground(t_level *lvl);
bool		create_screen_images(t_data *data);
bool		create_torch_images(t_data *data);
void		fl_sprite_setup(t_data *data);
bool		new_level_node(t_data *data);

bool		parse_map(char *filename, t_data *data);
char		**extract_map(char *file);
bool		validate_map(t_data *data);
int			map_col_len(char **map);
int			map_row_len(char **map);
char		**resize_to_rectangular(char **map);

// Utility functions

int64_t		get_time(void);
float		to_radian(int degrees);
void		space_to_one(char **map);
bool		print_error(t_errors error, bool warning);
bool		is_wall(t_level	*lvl, int x, int y);
bool		is_closed_door(t_level *lvl, int x, int y);
int			get_sprite_type(t_level *lvl, int x, int y);

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

// Door actions

void		door_action(t_data *data);
void		move_door(t_level *instance);
void		move_exit(t_level *lvl);

// Monster actions

void		monster_action(t_level *lvl);

// Flashlight logic

void		flashlight_switch(t_torch *torch);
void		flashlight_state(t_torch *torch);
void		flashlight_battery(t_torch *torch);
void		flashlight_disable(t_torch *torch);

// Renderer

void		delete_level_images(t_level *lvl);
void		reset_foreground(t_level *lvl);
void		render_surfaces(t_level *lvl, t_player *p);
bool		raycast(t_ray *ray, t_level *lvl, t_player *p, int x);
uint32_t	nearest_neighbor(mlx_texture_t *tex, uint32_t x, uint32_t y);
int			scale_texture_height(t_line *line);
void		image_fill(mlx_image_t *img, uint32_t color);
void		draw_fog(t_ray *ray, t_level *lvl, int x);

// Lighting

void		draw_light(t_level *lvl, t_line *line, int x, float distance);
void		light_floor(t_level *lvl, t_line *line, int x);
uint32_t	light_level(uint32_t shade, uint32_t bright, int level);
int			attenuation_factor(int level, float distance);
int			light_step(int x, t_shade shader, int amount);

// Renderer utils

float		calc_sprite_pos(t_sprite_data *sprite, t_ray *r, t_player *p);
void		line_init(t_line *line, float distance);

// Render door

uint32_t	pick_sprite_texture(t_sprite_data *sprite, t_level *lvl, int y);
void		save_sprite_data(t_ray *r, t_player *p);
void		save_door_data(t_ray *r, t_player *p);
void		draw_sprites(t_ray *ray, t_level *lvl, int x);

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
