/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:21:00 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/03 15:21:02 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

// Window configuration
# define W_WIDTH 1920
# define W_HEIGHT 1080
# define TITLE "John Carmero"

// ANSI color macros
# define RED "\033[1;31m"
# define YLW "\033[1;33m"
# define CLR "\033[0m"

// Parsing
# define SEPARATOR " \v\t\f\r\n"
# define VALUE_SEPARATOR " .,\t\v"
# define NUMBERS "0123456789"
# define CONT 1
# define STOP 0
# define CRITICAL -1

// Rendering constants
# define FPS 60
# define MSEC_PER_FRAME 16L
# define FOV 60
# define DOF 16
# define TILE 128

// Raycasting
# define VERTICAL 0
# define HORIZONTAL 1

// Movement and angles
# define PI 3.14159265359
# define DEGREE 0.01745329251
# define FOV_RAD (FOV * DEGREE)
# define ROTATE_AMOUNT 0.1
# define TRIG_MULTIPLIER 5

// Unit circle angles
# define UP (PI / 2.0)
# define DOWN ((3.0 * PI) / 2.0)
# define LEFT (PI)
# define RIGHT (0)

#endif
