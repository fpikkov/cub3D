/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:42:46 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/05 16:42:48 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	terminate(t_data *data)
{
	if (!data)
		return ;
	if (data->levels)
		delete_levels(data);
	if (data->mlx)
		mlx_terminate(data->mlx);
}
