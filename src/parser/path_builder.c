/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:41:40 by fpikkov           #+#    #+#             */
/*   Updated: 2025/04/08 13:41:42 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	dirs_to_root(char *program_name)
{
	int	amount;
	int	i;

	amount = 0;
	i = 0;
	while (program_name[i])
	{
		if (program_name[i] == '/')
			amount++;
		i++;
	}
	return (amount);
}

static int	truncate_path(char *path, int distance, t_data *data)
{
	int		trunc_dist;
	size_t	i;

	trunc_dist = 0;
	i = 0;
	while (trunc_dist < distance - 1 && path[i])
	{
		if (path[i] == '/')
			trunc_dist++;
		i++;
	}
	data->file.root = ft_substr(path, 0, i);
	if (!data->file.root)
		return (CRITICAL);
	return (CONT);
}

/**
 * @brief Checks where the process is being launched from
 */
int	build_path(char *path, t_data *data)
{
	int	distance;

	distance = dirs_to_root(path);
	if (distance != 2)
		data->file.build = true;
	else
		return (CONT);
	if (distance == 1)
	{
		data->file.root = ft_calloc(ft_strlen("../"), sizeof(char));
		if (!data->file.root)
			return (CRITICAL);
		ft_strlcpy(data->file.root, "../", 4);
	}
	else if (distance > 2)
	{
		if (truncate_path(path, distance, data) == CRITICAL)
			return (CRITICAL);
	}
	return (CONT);
}
