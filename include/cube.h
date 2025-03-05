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
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "MLX42.h"

# include "types.h"
# include "constants.h"

// Parsing functions

bool	parse_data(int argc, char **argv, t_data *data);
bool	parse_textures(char *filename, t_data *data);
int		parse_color_data(int fd, t_level *lvl);
bool	new_level_node(t_data *data);

// Utility functions

void	print_error(t_errors error, bool warning);

// Cleanup functions

void	delete_levels(t_data *data);

#endif
