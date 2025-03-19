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

# define MAPTILE 8
# define WIDTH 256
# define HEIGTH 256

typedef struct s_minimap
{
	mlx_t	*mlx;
	char	**map;
	mlx_image_t	*wall;
	mlx_image_t	*floor;
}		t_minimap;
#endif
