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
# define TITLE "Out-of-Bounds"

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

// Euler angles
# define PI 3.14159265359f
# define PI2 6.28318530717f
# define PI_DIAGONAL 1.57079632679f
# define DEGREE 0.01745329251f

// Movement and rotation constants
# define MOVE_SPEED 1.4f
# define ROTATE_AMOUNT MOVE_SPEED
# define BOUNDARY 0.4f
# define DPI 100

// Unit circle angles (flipped when working with arrays)
# define DOWN PI_DIAGONAL
# define UP 4.71238898038f
# define LEFT PI
# define RIGHT 0

// Minimap constants
# define RANGE 5
# define MINIMAP_SIZE 256.0f
# define PLAYER_COLOR 0x39FF14FF
# define WALL_COLOR 0x00008B30
# define FLOOR_COLOR 0xDC143CFF

// Flashlight constants
# define SHADE_COLOR 0x000000C8
# define TRANSPARENCY 0x000000A0
# define CIRCLE_RADIUS 270U
# define CIRCLE_STEP 16U
# define SAMPLE_SIZE 2U

// Image depths
# define BG_DEPTH 0
# define FG_DEPTH 1
# define FL_DEPTH 2
# define MM_DEPTH 3

#endif
