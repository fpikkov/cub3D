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

static const char	*g_message[13] = {
	"missing argument to map file",
	"ignoring multiple arguments",
	"invalid file extension",
	"unable to open file",
	"bytes read from file was less than expected",
	"multiple texture parameters found, defaulting to the first occurence",
	"map did not include the nescessary texture information",
	"unable to process texture information",
	"the given map is not enclosed by walls",
	"all empty cells could not be reached",
	"given map was not formatted correctly",
	"missing player position in the given map",
	"allocation failure"
};

void	print_error(t_errors error, bool warning, bool quit)
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
	if (quit)
	{
		ft_putendl_fd("exiting", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
