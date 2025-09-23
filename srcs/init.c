/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:10:24 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/23 16:12:17 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int initialise_data(t_data *data)
{
	data->mlx = mlx_init();
	data->game = malloc(sizeof(t_game));
	data->game->player = malloc(sizeof(t_player));
	data->game->player->x = 3;
	data->game->player->y = 3;
	data->game->plane_x = 0;
	data->game->plane_y = 0.66;
	data->game->dir_x = -1;
	data->game->dir_y = 0;
	// data->game->player->orientation = 's';
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
	data->zoom = 1.0;
	return (0);
}
