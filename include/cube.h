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

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "MLX42.h"

# include "types.h"
# include "constants.h"

// Parsing functions

bool	parse_data(char **argv, t_data *data);
bool	parse_textures(char *filename, t_data *data);
int		parse_color_data(int fd, t_level *lvl);
bool	load_color(char *buffer, t_level *lvl, int direction);
bool	new_level_node(t_data *data);

bool	parse_map(char *filename, t_data *data);
char	**extract_map(char *file);
bool	validate_map(t_data *data);

// Utility functions

void	space_to_zero(char **map);
bool	print_error(t_errors error, bool warning);

// Cleanup functions

void	free_map(char **map);
void	delete_levels(t_data *data);
void	terminate(t_data *data);

#endif
