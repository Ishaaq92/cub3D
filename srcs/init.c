/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:10:24 by isahmed           #+#    #+#             */
/*   Updated: 2025/10/09 20:23:44 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_textures(t_data *data)
{
	t_
	data->textures.north = load_xpm_to_img(data->mlx, data->map.path_to_NO);
	data->textures.south = load_xpm_to_img(data->mlx, data->map.path_to_SO);
	data->textures.west = load_xpm_to_img(data->mlx, data->map.path_to_WE);
	data->textures.east = load_xpm_to_img(data->mlx, data->map.path_to_EA);
}

static void reset_movement(t_data *data)
{
	data->player->forward = false;
	data->player->back = false;
	data->player->right = false;
	data->player->left = false;
	data->player->rotate_left = false;
	data->player->rotate_right = false;
}

void	set_orientation(t_data *data)
{
	data->game->dir_x = 0;
	data->game->dir_y = 0;
	data->game->plane_x = 0;
	data->game->plane_y = 0;
	if (data->player->orientation == 'N')
	{
		data->game->dir_y = -1;
		data->game->plane_x = -0.66;
	}
	if (data->player->orientation == 'S')
	{
		data->game->dir_y = 1;
		data->game->plane_x = 0.66;
	}
	if (data->player->orientation == 'W')
	{
		data->game->dir_x = -1;
		data->game->plane_y = 0.66;
	}
	if (data->player->orientation == 'E')
	{
		data->game->dir_x = 1;
		data->game->plane_y = -0.66;
	}
}

int initialise_data(t_data *data)
{
	reset_movement(data);
	data->mlx = mlx_init();
	data->game = malloc(sizeof(t_game));
	printf("x = %f\n", data->player->x);
	printf("y = %f\n", data->player->y);
	data->game->plane_x = 0;
	data->game->plane_y = 0.66;
	set_orientation(data);
	if (!data->mlx)
		return (-1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!data->win)
		return (-1);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.img)
		return (-1);
	data->img.pxls = mlx_get_data_addr(data->img.img, &data->img.bpp,
																		 &data->img.line_length, &data->img.endian);
	// data->zoom = 1.0;
	load_textures(data);
	return (0);
}
