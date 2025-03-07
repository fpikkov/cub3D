/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:40:08 by ahentton          #+#    #+#             */
/*   Updated: 2025/03/06 09:40:17 by ahentton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static	void	*free_null(char **str)
{
	free (*str);
	*str = NULL;
	return (NULL);
}

static	char	*map_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;
	int		sizetotal;

	if (!s1)
		return (NULL);
	sizetotal = (ft_strlen(s1) + ft_strlen(s2));
	ret = ft_calloc(sizeof(char), sizetotal + 1);
	if (ret == NULL)
	{
		free_null(&s1);
		free_null(&s2);
		return ((void *)print_error(SYS_MALLOC, false));
	}
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	j = -1;
	while (s2[++j])
		ret[i + j] = s2[j];
	free_null(&s1);
	return (ret);
}

static	char	*copy_file_data(char *file)
{
	int		fd;
	char	*line;
	char	*file_data;

	file_data = ft_calloc(1, 1);
	if (!file_data)
		return ((void *)print_error(SYS_MALLOC, false));
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(FILE_NO_OPEN, false);
		return (free_null(&file_data));
	}
	line = get_next_line(fd);
	if (!line)
		return (free_null(&file_data));
	while (line)
	{
		file_data = map_strjoin(file_data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (file_data);
}

static	int	find_map_start(char *file_data)
{
	int		i;
	int		line_start;

	i = 0;
	while (file_data[i])
	{
		line_start = i;
		while (file_data[i] && (file_data[i] == '1' || \
		file_data[i] == '0' || file_data[i] == ' '))
		{
			i++;
			if (file_data[i] && file_data[i] == '\n')
			{
				return (file_data[line_start]);
			}
		}
		while (file_data[i] && file_data[i] != '\n')
			i++;
		if (file_data[i] && file_data[i] == '\n')
			i++;
	}
	return (-1);
}

char	**extract_map(char *file)
{
	char	**map;
	char	*file_data;
	int		map_start;

	file_data = copy_file_data(file);
	if (!file_data)
		return (NULL);
	map_start = find_map_start(file_data);
	if (map_start < 0)
	{
		print_error(MAP_NO_START, false);
		return (free_null(&file_data));
	}
	map = ft_split(&file_data[map_start], '\n');
	if (!map)
	{
		print_error(SYS_MALLOC, false);
		return (free_null(&file_data));
	}
	space_to_zero(map);
	return (map);
}
