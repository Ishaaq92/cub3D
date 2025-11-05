/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:12:47 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:12:51 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_gun(t_data *data)
{
	int				x;
	int				y;
	int				gun_x;
	int				gun_y;
	unsigned int	color;

	gun_x = (WIDTH - data->textures.gun.width) / 2;
	gun_y = HEIGHT - data->textures.gun.height;
	y = 0;
	while (y < data->textures.gun.height)
	{
		x = 0;
		while (x < data->textures.gun.width)
		{
			color = get_pixel_img(&data->textures.gun, x, y);
			if ((color & 0x00FFFFFF) != 0x000000)
				pixel_put(gun_x + x, gun_y + y, &data->img, color);
			x++;
		}
		y++;
	}
}

t_img	load_xpm_to_img(void *mlx, char *path)
{
	t_img	tex;

	tex.img = mlx_xpm_file_to_image(mlx, path, &tex.width, &tex.height);
	if (!tex.img)
	{
		printf("Error: unable to load XPM file: %s\n", path);
		tex.width = 0;
		tex.height = 0;
		tex.pxls = NULL;
		tex.bpp = 0;
		tex.line_length = 0;
		tex.endian = 0;
		return (tex);
	}
	tex.pxls = mlx_get_data_addr(tex.img, &tex.bpp, &tex.line_length,
			&tex.endian);
	if (!tex.pxls)
	{
		printf("Error: unable to get data address for: %s\n", path);
		mlx_destroy_image(mlx, tex.img);
		tex.img = NULL;
	}
	return (tex);
}

/*Generate checkerboard floor texture testing generated floor tiles here.
  This is not part of the poject.*/
// void	generate_floor_texture(t_data *data)
// {
// 	int		x;
// 	int		y;
// 	int		color;
// 	char	*dst;
// 	t_img	tex;

// 	tex.img = mlx_new_image(data->mlx, TEX_WIDTH, TEX_HEIGHT);
// 	if (!tex.img)
// 		printf("Unable to create mlx image\n");
// 	tex.pxls = mlx_get_data_addr(tex.img, &tex.bpp, &tex.line_length,
// 			&tex.endian);
// 	data->textures.floor = tex;
// 	data->textures.floor.width = TEX_WIDTH;
// 	data->textures.floor.height = TEX_HEIGHT;
// 	for (y = 0; y < TEX_HEIGHT; y++)
// 	{
// 		for (x = 0; x < TEX_WIDTH; x++)
// 		{
// 			if ((x / 8 + y / 8) % 2 == 0)
// 				color = 0x505050; // Dark gray
// 			else
// 				color = 0x808080; // Light gray
// 			dst = data->textures.floor.pxls + (y
// 					* data->textures.floor.line_length + x
// 					* (data->textures.floor.bpp / 8));
// 			*(unsigned int *)dst = color;
// 		}
// 	}
// }
