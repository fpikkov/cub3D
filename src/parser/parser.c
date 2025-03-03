/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:34:12 by fpikkov           #+#    #+#             */
/*   Updated: 2025/03/03 13:34:13 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static bool	check_ext(const char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext)
		return (false);
	if (ft_strncmp(ext, ".cub", 5))
		return (false);
	return (true);

}

/**
 * @brief Parses data given in as program argument
 * @param data struct to game data passed in by pointer to the struct
 * @return true if successfull, otherwise false
 */
bool	parse_data(int argc, char **argv, t_data *data)
{
	if (argc < 2)
		print_error(FILE_NO_ARGS, false, true);
	if (argc > 2)
		print_error(FILE_MULTIPLE_ARGS, true, false);
	if (!check_ext(argv[1]))
		print_error(FILE_INVALID_EXTENSION, false, true);
	// TODO: check the textures and colors, store them in a struct. Can do during first read.
	// TODO: read lines from the file, check how many lines neeed to be allocated
	// and how big the longest line is.

	return (true);
}
