/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:39:44 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/14 13:39:45 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	map_col_len(char **map)
{
	int	len;
	int	x;
	int	y;

	len = 0;
	y = 0;
	while (map[y])
	{
		x = ft_strlen(map[y]);
		if (x > len)
			len = x;
		y++;
	}
	return (len);
}

int	map_row_len(char **map)
{
	int	len;

	len = 0;
	while (map[len])
		len++;
	return (len);
}

static char	*resize_element(char *row, int len)
{
	char	*temp;

	if (!row || len == 0)
		return (NULL);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return ((void *)print_error(SYS_MALLOC, false));
	ft_memset(temp, ' ', sizeof(char) * len);
	ft_memcpy(temp, row, ft_strlen(row));
	return (temp);
}

char	**resize_to_rectangular(char **map)
{
	char	**resized;
	int		longest;
	int		idx;

	resized = ft_calloc(map_row_len(map) + 1, sizeof(char *));
	if (!resized)
		return ((void *)print_error(SYS_MALLOC, false));
	longest = map_col_len(map);
	idx = 0;
	while (map[idx])
	{
		resized[idx] = resize_element(map[idx], longest);
		if (!resized[idx])
		{
			free_map(resized);
			return (NULL);
		}
		idx++;
	}
	space_to_one(resized);
	return (resized);
}
