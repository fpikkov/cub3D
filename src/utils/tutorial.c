/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tutorial.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:43:17 by fpikkov           #+#    #+#             */
/*   Updated: 2025/04/28 12:43:20 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	*g_help[10] = {
	"--------------------------- Controls ---------------------------",
	"Movement:		W, A, S, D",
	"Rotation:		mouse or arrow keys",
	"Door opening:		E",
	"Flashlight toggle:	left click or spacebar",
	"Minimap toggle:		M or Tab",
	"Skip level:		Ctrl + N",
	"Mouse unlock:		U",
	"----------------------------------------------------------------"
};

void	print_tutorial(void)
{
	ft_putstr_fd(CYAN, STDOUT_FILENO);
	ft_putendl_fd(g_help[0], STDOUT_FILENO);
	ft_putendl_fd(g_help[1], STDOUT_FILENO);
	ft_putendl_fd(g_help[2], STDOUT_FILENO);
	ft_putendl_fd(g_help[3], STDOUT_FILENO);
	ft_putendl_fd(g_help[4], STDOUT_FILENO);
	ft_putendl_fd(g_help[5], STDOUT_FILENO);
	ft_putendl_fd(g_help[6], STDOUT_FILENO);
	ft_putendl_fd(g_help[7], STDOUT_FILENO);
	ft_putendl_fd(g_help[8], STDOUT_FILENO);
	ft_putstr_fd(CLR, STDOUT_FILENO);
}
