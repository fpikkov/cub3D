// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   minimap.h                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ahentton <ahentton@student.hive.fi>        +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/03/12 13:13:01 by ahentton          #+#    #+#             //
//   Updated: 2025/03/12 13:13:33 by ahentton         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cube.h"

typedef struct s_minimap
{
	mlx_image_t	*minimap;
	int		player_x;
	int		player_y;
	int		start_x;
	int		start_y;
	int		map_x;
	int		map_y;
	float		tile_size;
	int		range;
}		t_minimap;
#endif
