/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight_images.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:16:35 by fpikkov           #+#    #+#             */
/*   Updated: 2025/04/08 15:16:36 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	*g_torches[LIGHT_SPRITES] = {
	"./textures/flashlight_off.png",
	"./textures/flashlight_1.png",
	"./textures/flashlight_2.png",
	"./textures/flashlight_3.png",
	"./textures/flashlight_4.png",
	"./textures/flashlight_5.png"
};

static void	fl_tex_to_img(t_data *data, size_t idx, mlx_texture_t *tex)
{
	if (idx == 0)
		data->torch.off = mlx_texture_to_image(data->mlx, tex);
	else if (idx == 1)
		data->torch.one = mlx_texture_to_image(data->mlx, tex);
	else if (idx == 2)
		data->torch.two = mlx_texture_to_image(data->mlx, tex);
	else if (idx == 3)
		data->torch.three = mlx_texture_to_image(data->mlx, tex);
	else if (idx == 4)
		data->torch.four = mlx_texture_to_image(data->mlx, tex);
	else if (idx == 5)
		data->torch.five = mlx_texture_to_image(data->mlx, tex);
}

static mlx_texture_t	*fl_load_tex(char *filename, t_file *info)
{
	char			*path;
	mlx_texture_t	*tex;

	path = filename;
	if (info->build)
	{
		path = ft_strjoin(info->root, filename);
		if (!path)
			return ((void *)print_error(SYS_MALLOC, false));
		tex = mlx_load_png(path);
		if (path)
			free(path);
		path = NULL;
	}
	else
		tex = mlx_load_png(path);
	if (!tex)
		return ((void *)print_error(TEXTURE_FAILURE, false));
	return (tex);
}

bool	create_torch_images(t_data *data)
{
	size_t			idx;
	mlx_texture_t	*tex;

	idx = 0;
	while (idx < LIGHT_SPRITES - 1)
	{
		tex = fl_load_tex(g_torches[idx], &data->file);
		if (!tex)
			return (false);
		fl_tex_to_img(data, idx, tex);
		mlx_delete_texture(tex);
		tex = NULL;
		idx++;
	}
	if (!data->torch.off || !data->torch.one || !data->torch.two \
	|| !data->torch.three || !data->torch.four || !data->torch.five)
		return (print_error(IMG_FAILURE, false));
	fl_sprite_setup(data);
	return (true);
}
