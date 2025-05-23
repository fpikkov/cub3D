/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:21:42 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/03 14:21:44 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	*g_message[26] = {
	"missing argument to map file(s)",
	"invalid file extension",
	"unable to open file",
	"bytes read from file was less than expected",
	"map did not include the necessary texture information",
	"image creation failed",
	"parsed texture was not a png file",
	"unable to process texture information",
	"failed to convert texture to image",
	"the given map is not enclosed by walls",
	"all empty cells could not be reached",
	"given map was not formatted correctly",
	"missing player position in the given map",
	"no starting point for the map detected",
	"unknown characters detected in the given map",
	"too many player positions detected in the given map",
	"the given map is not closed properly",
	"allocation failure",
	"failed to fetch root directory of the project",
	"failed to resize image",
	"hook creation failure",
	"given value is outside the color channel range, limiting to max value",
	"missing value in color information, defaulting to maximum channel value",
	"ignoring letters found in color values, hexadecimal values not accepted",
	"ignoring signedness in color information"
};

/**
 * @brief Prints an error message based on the given error enumerator
 * @param error error enum
 * @param warning should we print a warning instead of messsage
 * @return false in most cases unless exiting program
 */
bool	print_error(t_errors error, bool warning)
{
	if (!warning)
	{
		ft_putstr_fd(RED, STDERR_FILENO);
		ft_putstr_fd("error: ", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(YLW, STDERR_FILENO);
		ft_putstr_fd("warning: ", STDERR_FILENO);
	}
	ft_putendl_fd(g_message[(error - 200)], STDERR_FILENO);
	ft_putstr_fd(CLR, STDERR_FILENO);
	if (error == FILE_NO_ARGS)
		return (true);
	return (false);
}
