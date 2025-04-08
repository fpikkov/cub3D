/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:23:11 by fpikkov           #+#    #+#             */
/*   Updated: 2025/04/08 14:23:13 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*tex_join_path(char *buf, size_t st, size_t len, t_file *info)
{
	char	*path;
	char	*joined;

	joined = NULL;
	path = ft_substr(buf, st, len);
	if (!path)
		return (NULL);
	if (info->build)
	{
		joined = ft_strjoin(info->root, path);
		if (path)
			free(path);
		path = NULL;
		if (!joined)
			return (NULL);
		else
			path = joined;
	}
	return (path);
}
