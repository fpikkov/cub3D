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
# include "MLX42.h"
# include <stdbool.h>

enum e_errors
{
	FILE_NO_ARGS = 200,
	FILE_INVALID_EXTENSION,
	FILE_BYTES_READ,
	MAP_MISSING_WALLS,
	MAP_INVALID_PATH,
	MAP_INVALID_FORMAT,
	MAP_NO_PLAYER,
};

#endif
